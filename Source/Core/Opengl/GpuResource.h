#pragma once

#include <optional>
#include "GL/glew.h"


class GpuResource {
public:
	using THandle = GLuint;

	GpuResource() = default;
	virtual ~GpuResource() = default;

	const std::optional<THandle>& GetHandle() const;
	virtual bool IsValid() const;

	virtual bool Construct();
	virtual bool Reconstruct();
	virtual void Destroy();


protected:
	virtual std::optional<THandle> CreateHandle() = 0;
	virtual void DestroyHandle(THandle handle) = 0;

	virtual bool Init();


private:
	std::optional<THandle> _handle;
};
