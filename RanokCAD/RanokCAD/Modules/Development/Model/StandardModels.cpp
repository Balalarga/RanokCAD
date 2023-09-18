#include "StandardModels.h"

#include <format>
#include <sstream>
#include "RanokLang/Parser.h"


Parser sParser;


ActionTree StandardModels::GetCube(float size)
{
	std::ostringstream codeStream;
	codeStream << "def main(s[3]){\n";
	codeStream << std::format("return {}^2 - (s[0]-3)^2.0 - s[1]^2.0 - (s[2] + 2)^2.0;", size);
	codeStream << "\n}";

	return ActionTree(sParser.Parse(codeStream.str()));
}

ActionTree StandardModels::GetSphere(float radius)
{
	std::ostringstream codeStream;
	codeStream << "def main(s[3]){\n";
	codeStream << std::format("return {}^2 - (s[0]-3)^2.0 - s[1]^2.0 - (s[2] + 2)^2.0;", radius);
	codeStream << "\n}";

	return ActionTree(sParser.Parse(codeStream.str()));
}
