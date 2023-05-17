#pragma once
#include <GL/glew.h>
#include <glm/vec2.hpp>

#include "VramHandle.h"

class Texture: public VramHandle
{
public:
	Texture(glm::ivec2 size, int inDataType, int outDataType);
	Texture(glm::ivec2 size, int channels);

	bool InitWithData(const unsigned char* data);

	void Bind(unsigned slot = 0) const;
	static void Release();

	void ReadPixels(void* pixels);

	const glm::ivec2& GetSize() const
	{
		return _size;
	}


protected:
	bool Init() override;
	bool PostInit() override;

	int AllocateVram() override;
	void DeallocateVram() override;

private:
	glm::ivec2 _size;
	int _inDataType = GL_RGB8;
	int _outDataType = GL_RGB;
};
