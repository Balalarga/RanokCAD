#pragma once
#include "IGenerator.h"

class ShaderGenerator: public CppGenerator
{
public:
	void ProcessNode(std::stringstream& outCode, const BinaryNode* node) override;
	void ProcessNode(std::stringstream& outCode, const FunctionDeclarationNode* node) override;
};