#include <filesystem>
#include <fstream>
#include "App/Application.h"
#include "ClKernel/ClExecutor.h"
#include "ClKernel/FlatBuffer.h"
#include "ClKernel/MultiDimSpace.h"
#include "Cli/AppArgs.h"
#include "Language/Generators/OpenclGenerator.h"
#include "Language/Parser.h"
#include "Window/Window.h"
#include "argparse/argparse.hpp"
#include "spdlog/spdlog.h"

int UiMode()
{
	WindowParams windowParams;
	windowParams.vSync = true;
	Window::SetParams(windowParams);

	Application app(Window::Get());
	app.Launch();
	return 0;
}

int CliMode()
{
	ClExecutor::Init();
	// initialize opengl context
	Window::Get();

	std::filesystem::path filepath = AppArgs::GetParser().get<std::string>("-filepath");
	if (!exists(filepath))
	{
		spdlog::error("File '{}' doesn't exists", filepath.string());
		return -1;
	}

	std::ifstream fileReader(filepath);
	if (!fileReader)
	{
		spdlog::error("Cannot open file '{}'", filepath.string());
		return -1;
	}

	std::stringstream fileContentStream;
	fileContentStream << fileReader.rdbuf();
	std::string fileContent = fileContentStream.str();

	Parser parser;
	auto program = parser.Parse(Lexer(fileContent));
	if (!program.Root())
	{
		spdlog::error("Cannot parse code:\n{}", fileContent);
		return -1;
	}

	OpenclGenerator generator;
	auto generatedCode = generator.Generate(program).value_or("");
	if (generatedCode.empty())
	{
		spdlog::error("Cannot generate code:\n{}", fileContent);
		return -1;
	}

	ClExecutor executor;
	executor.Compile(generatedCode);

	std::vector<double> center{0, 0, 0};
	std::vector<double> spaceSize{10, 10, 10};
	int depth{5};
	auto outputFilepath = filepath.replace_extension(".rfbin");

	FlatArray<MImage3D> imageBuffer;

	MultiDimSpace space(center, spaceSize, depth);
	std::ofstream file(outputFilepath, std::ios_base::binary);
	auto calculateCallback = [&file, &imageBuffer](size_t start, size_t count)
	{
		if (!imageBuffer.WritePart(file, count))
		{
			spdlog::error("File writing failed");
		}
	};

	size_t batchSize = 0;
	if (file)
	{
		file << space;

		cl_int startId = 0;
		cl_uint3 clSpaceSize = {
			static_cast<unsigned>(space.GetPartition()[0]),
			static_cast<unsigned>(space.GetPartition()[1]),
			static_cast<unsigned>(space.GetPartition()[2])};

		cl_double3 startPoint = {space.GetStartPoint()[0], space.GetStartPoint()[1], space.GetStartPoint()[2]};
		cl_double3 pointSize = {space.GetUnitSize()[0], space.GetUnitSize()[1], space.GetUnitSize()[2]};
		cl_double3 halfSize = {pointSize.x / 2., pointSize.y / 2., pointSize.z / 2.};

		size_t spaceFlatSize = space.GetTotalPartition();
		size_t bufferSize;
		if (batchSize != 0 && batchSize < spaceFlatSize)
			bufferSize = batchSize;
		else
			bufferSize = spaceFlatSize;

		imageBuffer.Resize(bufferSize);

		std::vector<ClKernelArguments::Argument> opt{
			{&startId, sizeof(cl_int)},
			{&clSpaceSize, sizeof(cl_uint3)},
			{&startPoint, sizeof(cl_double3)},
			{&pointSize, sizeof(cl_double3)},
			{&halfSize, sizeof(cl_double3)},
		};

		ClKernelArguments::Argument result(&imageBuffer[0], sizeof(imageBuffer[0]), imageBuffer.Size());

		int retCode = CL_SUCCESS;
		for (size_t mStartId = 0; mStartId < spaceFlatSize; mStartId += bufferSize)
		{
			retCode = executor.ExecuteCurrentKernel(OpenclGenerator::sKernelProgram, ClKernelArguments(result, opt));

			if (retCode != CL_SUCCESS)
				break;

			if (mStartId + bufferSize > spaceFlatSize)
				bufferSize = spaceFlatSize - mStartId;

			calculateCallback(mStartId, bufferSize);
		}

		if (retCode == CL_SUCCESS)
		{
			spdlog::info("MImage build succeed");
		}
		else
		{
			spdlog::error("MImage build failed: {}", retCode);
		}

		file.close();
	}

	ClExecutor::Destroy();
	return 0;
}


int main(int argc, char** argv)
{
	auto& parser = AppArgs::GetParser();

	parser.add_argument("-uiMode").default_value(false).implicit_value(true);
	parser.add_argument("-filepath");
	parser.add_argument("-depth").default_value(5);

	if (!AppArgs::Init(argc, argv))
	{
		return -1;
	}

	if (parser["-uiMode"] == true)
	{
		return UiMode();
	}

	return CliMode();
}
