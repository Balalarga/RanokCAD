#pragma once

class RenderTarget
{
public:
	RenderTarget() = default;
	virtual ~RenderTarget() = default;

	void Clear();

	virtual void Present() = 0;

	virtual void Bind() = 0;
	virtual void Release() = 0;
};
