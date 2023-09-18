#pragma once
#include "ShaderGenerator.h"


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


class JsonGenerator: public ShaderGenerator
{
public:
	void ProcessNode(std::stringstream& outCode, const FunctionDeclarationNode* node) override;

	JsonGeneratorFunctionObject FlushObject();


private:
	JsonGeneratorFunctionObject _object;
};
