#pragma once
#include "RanokLang/ActionTree.h"

class StandardModels
{
public:
	StandardModels() = delete;
	StandardModels(StandardModels&&) = delete;
	StandardModels(const StandardModels&) = delete;

	static ActionTree GetCube();
	static ActionTree GetSphere();
};
