#pragma once
#include "RanokLang/Generators/ShaderGenerator.h"


struct JsonGeneratorFunctionArg
{
	std::string name;
	std::string type;
	size_t count;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(JsonGeneratorFunctionArg, name, type, count)
};

struct JsonGeneratorFunctionObject
{
	std::string body;
	std::vector<JsonGeneratorFunctionArg> args;
	std::vector<JsonGeneratorFunctionObject> functions;
	
	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(JsonGeneratorFunctionObject, body, args, functions)
};


class AssemblyCodeGenerator: public ShaderGenerator
{
public:
	void ProcessNode(std::stringstream& outCode, const FunctionDeclarationNode* node) override;

	JsonGeneratorFunctionObject FlushObject();
	void SetAssemblyPart(const class AssemblyPart* part);


private:
	JsonGeneratorFunctionObject _object;
	const AssemblyPart* _part = nullptr;
};
