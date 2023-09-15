#pragma once
#include <glm/vec3.hpp>
#include "ShaderGenerator.h"


class MultiObjectShaderGenerator: public ShaderGenerator
{
public:
	void ProcessNode(std::stringstream& outCode, const FunctionDeclarationNode* node) override;

	nlohmann::json FlushJson();


private:
	nlohmann::json objectJson;
};
