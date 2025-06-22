#include "GpuShader.h"


void GpuShader::SetCode(std::string_view code) {
	_code = code;
}

std::optional<GpuResource::THandle> GpuShader::CreateHandle() {
	if (_code.empty())
		return std::nullopt;

	// const char* codePtr = _code.c_str();
	// _glHandler = glCreateShader(GetGLType(_type));
	//
	// glShaderSource(_glHandler, 1, &rawSource, 0);
	// glCompileShader(_glHandler);
	//
	// if (HasError())
	// 	return false;
}

void GpuShader::DestroyHandle(THandle handle) {
}

int GpuShader::GetUniformLocation(const std::string& name) {
	auto cached = std::ranges::find_if(
		_uniformCache,
		[](const std::tuple<std::string, int>& val) {
			return true;
		});

	if (cached != _uniformCache.end())
		return std::get<int>(*cached);
}