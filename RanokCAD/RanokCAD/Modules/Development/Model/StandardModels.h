#pragma once
#include "RanokLang/ActionTree.h"

class StandardModels
{
public:
	StandardModels() = delete;
	StandardModels(StandardModels&&) = delete;
	StandardModels(const StandardModels&) = delete;

	static ActionTree GetCube(float size = 1);
	static ActionTree GetSphere(float radius = 1);
};
