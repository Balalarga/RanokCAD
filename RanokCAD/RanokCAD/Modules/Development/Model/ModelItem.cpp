#include "ModelItem.h"

#include "RanokLang/Lexer.h"
#include "RanokLang/Parser.h"

ShaderGenerator ModelItem::sGenerator;

ModelItem::ModelItem(const std::string& newCode, glm::vec3 newBounding)
{
	UpdateCode(newCode, newBounding);
}

bool ModelItem::UpdateCode(const std::string& newCode, glm::vec3 newBounding)
{
	Parser parser;
	ActionTree newProgram = parser.Parse(Lexer{newCode});
	if (parser.HasErrors() || newProgram.Root())
		return false;

	_program = newProgram;
	_code = newCode;
	_bounding = newBounding;
	return true;
}

std::optional<std::string> ModelItem::GetShaderCode() const
{
	return sGenerator.Generate(_program);
}

void ModelTree::DrawItem()
{
}

std::string ModelTree::GetTitle() const
{
	return "NewNode";
}
