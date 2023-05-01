#include "VramHandle.h"

bool VramHandle::Construct(bool bForce)
{
	if (IsValid() && !bForce)
		return true;

	_handle = AllocateVram();
	if (_handle != 0 && PreInit() && Init() && PostInit())
		return true;

	Destroy();

	return false;
}

bool VramHandle::PreInit()
{
	return true;
}

bool VramHandle::Init()
{
	return true;
}

bool VramHandle::PostInit()
{
	return true;
}

void VramHandle::Destroy()
{
	if (IsValid())
	{
		DeallocateVram();
		_handle = 0;
	}
}
