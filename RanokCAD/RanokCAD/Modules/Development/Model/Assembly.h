#pragma once
#include <string>

#include "Model.h"
#include "RanokLang/Generators/MultiObjectShaderGenerator.h"
#include "Utils/DenseTree.h"


class Assembly
{
public:

	

private:
	DenseTree<std::string, Model> _models;
	MultiObjectShaderGenerator _codeGenerator;
};
