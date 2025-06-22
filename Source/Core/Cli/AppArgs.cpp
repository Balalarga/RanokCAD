#include "AppArgs.h"
#include "spdlog/spdlog.h"

std::string AppArgs::_sAppName;

void AppArgs::SetAppName(std::string_view appName)
{
	assert(_sAppName.empty());
	_sAppName = appName;
}

AppArgs& AppArgs::Get()
{
	static AppArgs inst;
	return inst;
}

bool AppArgs::Init(
	std::string_view appName
	, int argc
	, char** argv
	, std::function<void(argparse::ArgumentParser&)>&& argsSetup)
{
	_sAppName = appName;
	try {
		auto& parser = GetParser();
		argsSetup(parser);
		parser.parse_args(argc, argv);
		return true;
	}
	catch (const std::exception& error) {
		spdlog::critical(error.what());
		return false;
	}
}

bool AppArgs::Init(int argc, char** argv, std::function<void(argparse::ArgumentParser&)>&& argsSetup)
{
	try {
		auto& parser = GetParser();
		argsSetup(parser);
		parser.parse_args(argc, argv);
		return true;
	}
	catch (const std::exception& error) {
		spdlog::critical(error.what());
		return false;
	}
}

bool AppArgs::Parse(const std::string_view argName)
{
	return GetParser().is_used(argName);
}

argparse::ArgumentParser& AppArgs::GetParser()
{
	return Get()._argParser;
}
