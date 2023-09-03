#pragma once
#include <glm/vec3.hpp>
#include "ShaderGenerator.h"


class MultiObjectShaderGenerator: public ShaderGenerator
{
public:
	void ProcessNode(std::stringstream& outCode, const FunctionDeclarationNode* node) override;

	nlohmann::json FlushJson();

	void SetColor(float r, float g, float b, float a = 1);
	void SetPosition(const glm::vec3& pos);


private:
	nlohmann::json objectJson;
};
