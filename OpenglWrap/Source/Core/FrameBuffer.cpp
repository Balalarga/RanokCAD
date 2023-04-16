#include "FrameBuffer.h"

#include <GL/glew.h>

FrameBuffer::FrameBuffer(const Texture& texture) : _texture(texture)
{
}

FrameBuffer::FrameBuffer(glm::ivec2 size, int channels) : _texture(size, channels)
{
}

FrameBuffer::~FrameBuffer()
{
	FrameBuffer::Destroy();
}

bool FrameBuffer::Init()
{
	if (!VramHandle::Init() || !_texture.Init())
		return false;

	Bind();

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture.GetHandle(), 0);

	Release();

	return true;
}

void FrameBuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, GetHandle());
}

void FrameBuffer::Release()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::Present()
{
}

int FrameBuffer::AllocateVram()
{
	unsigned handle;

	glGenFramebuffers(1, &handle);

	return static_cast<int>(handle);
}

void FrameBuffer::DeallocateVram()
{
	unsigned handle = GetHandle();
	glDeleteFramebuffers(1, &handle);
}
