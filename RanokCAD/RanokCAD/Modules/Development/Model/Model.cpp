#include "Model.h"

#include "AssemblyCodeGenerator.h"
#include "RanokLang/Parser.h"


Model::Model(std::string name)
	: IModelBase(std::move(name))
{
}

nlohmann::json Model::GenerateJson() const
{
	static AssemblyCodeGenerator generator;
	generator.Generate(_functionTree);
	return {
		{"Name", GetName()},
		{"Function", generator.FlushObject()},
	};
}

void Model::SetFunctionCode(const std::string& code)
{
	static Parser parser;
	_functionTree = parser.Parse(Lexer(code));
}

void Model::SetFunctionTree(const ActionTree& tree)
{
	_functionTree = tree;
}
