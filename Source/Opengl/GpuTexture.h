#pragma once

#include <GL/glew.h>
#include "GpuResource.h"
#include "glm/vec2.hpp"


class GpuTexture: public GpuResource
{
public:
	GpuTexture(glm::ivec2 size, int inDataType, int outDataType);
	GpuTexture(glm::ivec2 size, int channels);

	bool InitWithData(const unsigned char* data);

	void Bind(unsigned slot = 0) const;
	static void Release();

	void ReadPixels(void* pixels);

	const glm::ivec2& GetSize() const
	{
		return _size;
	}


private:
	glm::ivec2 _size;
	int _sourceDataType = GL_RGB8;
	int _dataType = GL_RGB;
};
