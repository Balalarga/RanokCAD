#include "Texture.h"

#include <GL/glew.h>

Texture::Texture(glm::ivec2 size, int channels) : _size(size), _channels(channels)
{
}

Texture::Texture(glm::ivec2 size, int channels, const unsigned char* data) : _size(size), _channels(channels)
{
	Init(data);
}

Texture::~Texture()
{
	Texture::Destroy();
}

bool Texture::Init(const unsigned char* data)
{
	if (!VramHandle::Init())
		return false;

	Bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	if (_channels == 1)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, _size.x, _size.y, 0, GL_R, GL_UNSIGNED_BYTE, data);
	else if (_channels == 2)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RG8, _size.x, _size.y, 0, GL_RG, GL_UNSIGNED_BYTE, data);
	else if (_channels == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, _size.x, _size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	else
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _size.x, _size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	Release();

	return true;
}

int Texture::AllocateVram()
{
	unsigned handle;

	glGenTextures(1, &handle);

	return static_cast<int>(handle);
}

bool Texture::Init()
{
	return Init(nullptr);
}

void Texture::DeallocateVram()
{
	unsigned handle = GetHandle();
	glDeleteTextures(1, &handle);
}

void Texture::Bind(unsigned slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, GetHandle());
}

void Texture::Release()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
