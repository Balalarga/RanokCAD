#include "GpuResource.h"


const std::optional<int>& GpuResource::GetHandle() const
{
	return _handle;
}

bool GpuResource::Construct()
{
	if (IsValid())
		return true;

	_handle = CreateHandle();
	if (IsValid())
		return true;

	DestroyHandle();
	return false;
}

bool GpuResource::Reconstruct()
{
	Destroy();
	return Construct();
}

void GpuResource::Destroy()
{
	if (!IsValid())
		return;

	DestroyHandle();
	_handle.reset();
}

bool GpuResource::IsValid() const
{
	return _handle.has_value();
}

bool GpuResource::Init()
{
	return true;
}
