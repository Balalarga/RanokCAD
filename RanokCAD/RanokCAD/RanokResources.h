#pragma once

#include "ResourceManager/ResourceManager.h"

class RanokResources: public ResourceManager
{
public:
	static 
        RanokResources& Get();


protected:
	RanokResources() = default;
};
