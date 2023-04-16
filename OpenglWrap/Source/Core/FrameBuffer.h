#pragma once
#include "RenderTarget.h"
#include "Texture.h"


class FrameBuffer: public VramHandle, public RenderTarget
{
public:
	FrameBuffer(const Texture& texture);
	FrameBuffer(glm::ivec2 size, int channels);
	virtual ~FrameBuffer();

	bool Init() override;

	void Bind() override;
	void Release() override;
	void Present() override;

	const Texture& GetTexture() const { return _texture; }


protected:
	int AllocateVram() override;
	void DeallocateVram() override;


private:
	Texture _texture;
};
