#include "GpuShaderProgram.h"

#include <cassert>


void GpuShaderProgram::Bind() const {
	assert(IsValid());
	if (!IsValid())
		return;

	glUseProgram(GetHandle().value());
}

void GpuShaderProgram::Release() const {
	assert(IsValid());
	if (!IsValid())
		return;

	glUseProgram(0);
}

std::optional<GpuResource::THandle> GpuShaderProgram::CreateHandle() {
	return glCreateProgram();
}

void GpuShaderProgram::DestroyHandle(THandle handle) {
	glDeleteProgram(handle);
}