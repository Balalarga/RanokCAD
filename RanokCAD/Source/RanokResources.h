#pragma once
#include "ResourceManager.h"

class RanokResources: public ResourceManager
{
public:
	static RanokResources& Get();

protected:
	RanokResources() = default;
};
