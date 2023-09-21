#pragma once
#include "RanokLang/Generators/ShaderGenerator.h"


struct JsonGeneratorFunctionArg
{
	std::string Name;
	std::string Type;
	size_t Count;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(JsonGeneratorFunctionArg, Name, Type, Count)
};

struct JsonGeneratorFunctionObject
{
	std::string Body;
	std::vector<JsonGeneratorFunctionArg> Args;
	
	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(JsonGeneratorFunctionObject, Body, Args)
};


class AssemblyCodeGenerator: public ShaderGenerator
{
public:
	void ProcessNode(std::stringstream& outCode, const FunctionDeclarationNode* node) override;

	JsonGeneratorFunctionObject FlushObject();


private:
	JsonGeneratorFunctionObject _object;
};
