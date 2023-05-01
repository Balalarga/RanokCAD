#pragma once
#include "ShaderGenerator.h"

class MultiObjectShaderGenerator: public ShaderGenerator
{
public:
	void ProcessNode(std::stringstream& outCode, const FunctionDeclarationNode* node) override;

	nlohmann::json FlushJson();

	void SetColor(float r, float g, float b, float a = 1);


private:
	nlohmann::json objectJson;
};
