#include "FrameBuffer.h"

#include <ranges>

#include "gl/glew.h"

FrameBuffer::FrameBuffer(glm::ivec2 size) : _size(size)
{
}

FrameBuffer::~FrameBuffer()
{
	FrameBuffer::Destroy();
}

void FrameBuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, GetHandle());
	if (!_renderingBuffers.empty())
		glDrawBuffers(static_cast<int>(_renderingBuffers.size()), _renderingBuffers.data());
	glViewport(0, 0, _size.x, _size.y);
}

void FrameBuffer::Release()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::Present()
{
}

Texture* FrameBuffer::GetTexture(int type)
{
	auto it = _textures.find(type);
	if (it == _textures.end())
		return nullptr;

	return &it->second;
}

bool FrameBuffer::IsValid() const
{
	return VramHandle::IsValid();
}

bool FrameBuffer::PreInit()
{
	Bind();

	for (auto& texture : _textures | std::views::values)
	{
		if (!texture.Construct(true))
		{
			Release();
			return false;
		}
	}

	return true;
}

bool FrameBuffer::Init()
{
	for (auto& [type, texture] : _textures)
	{
		glFramebufferTexture2D(GL_FRAMEBUFFER, type, GL_TEXTURE_2D, texture.GetHandle(), 0);
	}

	Release();

	return true;
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
