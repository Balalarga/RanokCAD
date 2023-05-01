#include "RanokResources.h"

RanokResources& RanokResources::Get()
{
	static RanokResources inst;
	return inst;
}