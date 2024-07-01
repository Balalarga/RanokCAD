#pragma once

#include <optional>


class GpuResource
{
public:
	GpuResource() = default;
	virtual ~GpuResource() = default;

	const std::optional<int>& GetHandle() const;
	virtual bool IsValid() const;

	virtual bool Construct();
	virtual bool Reconstruct();
	virtual void Destroy();


protected:
	virtual int CreateHandle() = 0;
	virtual void DestroyHandle() = 0;

	virtual bool Init();


private:
	std::optional<int> _handle;
};
