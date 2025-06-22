#pragma once

#include <string>
#include <unordered_map>

#include "GpuResource.h"


class GpuShader : public GpuResource {
public:
	void SetCode(std::string_view code);


protected:
	std::optional<THandle> CreateHandle() override;
	void DestroyHandle(THandle handle) override;

	int GetUniformLocation(const std::string& name);


private:
	std::string _code;
	std::vector<std::tuple<std::string, int>> _uniformCache;
};
