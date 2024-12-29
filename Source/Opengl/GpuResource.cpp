#include "GpuResource.h"


const std::optional<GpuResource::THandle>& GpuResource::GetHandle() const {
	return _handle;
}

bool GpuResource::Construct() {
	if (IsValid())
		return true;

	_handle = CreateHandle();
	if (IsValid())
		return true;

	DestroyHandle(_handle.value());
	return false;
}

bool GpuResource::Reconstruct() {
	Destroy();
	return Construct();
}

void GpuResource::Destroy() {
	if (!IsValid())
		return;

	DestroyHandle(_handle.value());
	_handle.reset();
}

bool GpuResource::IsValid() const {
	return _handle.has_value();
}

bool GpuResource::Init() {
	return true;
}