#pragma once
#include "GpuResource.h"


class GpuShaderProgram : public GpuResource {
public:
	void Bind() const;
	void Release() const;


protected:
	std::optional<THandle> CreateHandle() override;
	void DestroyHandle(THandle handle) override;


private:
};
