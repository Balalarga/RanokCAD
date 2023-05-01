#pragma once
#include "IGenerator.h"

class OpenclGenerator: public CppGenerator
{
public:
	static const std::string sKernelProgram;

	std::string ProcessHardcodedFunc(Hardcoded::FuncNames func) override;

	void ProcessNode(std::stringstream& outCode, const BinaryNode* node) override;
	void ProcessNode(std::stringstream& outCode, const FunctionDeclarationNode* node) override;
};
