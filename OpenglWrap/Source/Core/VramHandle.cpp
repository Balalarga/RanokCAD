#include "VramHandle.h"


VramHandle::operator bool() const
{
	return _handle != 0;
}

bool VramHandle::Init()
{
	if (*this)
		return true;

	SetHandle(AllocateVram());

	return *this;
}

void VramHandle::Destroy()
{
	if (*this)
	{
		DeallocateVram();
		_handle = 0;
	}
}

void VramHandle::SetHandle(int handle, bool bNotExistsOnly)
{
	if (!bNotExistsOnly || _handle == 0)
		_handle = handle;
}
