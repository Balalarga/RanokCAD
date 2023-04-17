#include <iostream>

#include "../RanokLang/Source/Parser.h"
#include "RanokCADApp.h"
#include "RanokResources.h"
#include "ResourceManager.h"
#include "Generators/MultiObjectShaderGenerator.h"

int main(int argc, char** argv)
{
	constexpr auto resourceRegistry = "resourceRegistry.json";
	if (!RanokResources::Get().InitFrom(resourceRegistry))
	{
		std::cout << "Couldn't read " << resourceRegistry << std::endl;
		return -1;
	}

	RanokCADApp mainWindow;

	MultiObjectShaderGenerator generator;
	constexpr auto code1 = R"(
def main(s[3])
{
	r = 1;
	return r^2 - (s[0]-r)^2 - s[1]^2 - s[2]^2;
}
)";
	constexpr auto code2 = R"(
def s()
{
	return 1;
}

def main(s[3])
{
	r = s();
	return (r - s[0]^2 - s[1]^2 - s[2]^2)|(r - s[0]^2 - s[1]^2 - s[2]^2);
}
)";
	nlohmann::json objects;
	objects["Objects"] = {};
	Lexer lexer1(code1);
	Lexer lexer2(code2);
	Parser parser;
	ActionTree tree1 = parser.Parse(lexer1);
	if (std::optional<std::string> res = generator.Generate(tree1))
		objects["Objects"].push_back(generator.FlushJson());

	ActionTree tree2 = parser.Parse(lexer2);
	if (std::optional<std::string> res = generator.Generate(tree2))
		objects["Objects"].push_back(generator.FlushJson());

	auto path = std::filesystem::current_path();
	path /= "Templates/RayMarch.glsl.templ";

	// std::cout << objects.dump(2) << std::endl << std::endl;
	inja::Environment env;
	std::cout << env.render_file(path.string(), objects);

	mainWindow.Run();

	return 0;
}
