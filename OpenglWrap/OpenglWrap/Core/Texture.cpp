#include "Texture.h"

#include <GL/glew.h>

Texture::Texture(glm::ivec2 size, int inDataType, int outDataType) :
	_size(size), _inDataType(inDataType), _outDataType(outDataType)
{
}

Texture::Texture(glm::ivec2 size, int channels) : _size(size)
{
	if (channels == 1)
	{
		_inDataType = GL_R8;
		_outDataType = GL_R;
	}
	else if (channels == 2)
	{
		_inDataType = GL_RG8;
		_outDataType = GL_RG;
	}
	else if (channels == 3)
	{
		_inDataType = GL_RGB8;
		_outDataType = GL_RGB;
	}
	else
	{
		_inDataType = GL_RGBA8;
		_outDataType = GL_RGBA;
	}
}

bool Texture::InitWithData(const unsigned char* data)
{
	Bind();

	glTexImage2D(GL_TEXTURE_2D, 0, _inDataType, _size.x, _size.y, 0, _outDataType, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	Release();

	return true;
}

bool Texture::Init()
{
	return InitWithData(nullptr);
}

bool Texture::PostInit()
{
	return VramHandle::PostInit();
}

int Texture::AllocateVram()
{
	unsigned handle;

	glGenTextures(1, &handle);

	return static_cast<int>(handle);
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
