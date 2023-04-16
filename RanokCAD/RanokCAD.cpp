#include <iostream>

#include "../RanokLang/Source/Parser.h"
#include "Generators/ShaderGenerator.h"
#include "RanokCADApp.h"
#include "RanokResources.h"
#include "ResourceManager.h"

int main(int argc, char** argv)
{
	constexpr auto resourceRegistry = "resourceRegistry.json";
	if (!RanokResources::Get().InitFrom(resourceRegistry))
	{
		std::cout << "Couldn't read " << resourceRegistry << std::endl;
		return -1;
	}

	RanokCADApp mainWindow;

	ShaderGenerator generator;
	constexpr auto code1 = R"(
def main(s[3])
{
	return 1 - s[0]^2 - s[1]^2 - s[2]^2;
}
)";
	constexpr auto code2 = R"(
def main(s[3])
{
	return 1 - s[0]^2 - s[1]^2 - s[2]^2;
}
)";
	Lexer lexer1(code1);
	Lexer lexer2(code2);
	Parser parser;
	ActionTree tree1 = parser.Parse(lexer1);
	if (std::optional<std::string> res = generator.Generate(tree1))
		std::cout << res.value();

	auto path = std::filesystem::current_path();
	path /= "../RanokLang/Templates/Shader.tmpl";

	mainWindow.SetOnImGuiRender([] {});

	mainWindow.Run();

	return 0;
}
