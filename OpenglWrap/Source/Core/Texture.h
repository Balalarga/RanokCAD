#pragma once
#include <glm/vec2.hpp>

#include "VramHandle.h"

class Texture: public VramHandle
{
public:
	Texture(glm::ivec2 size, int channels);
	Texture(glm::ivec2 size, int channels, const unsigned char* data);
	virtual ~Texture();

	bool Init() override;
	bool Init(const unsigned char* data);

	void Bind(unsigned slot = 0) const;
	static void Release();


protected:
	int AllocateVram() override;
	void DeallocateVram() override;


private:
	glm::ivec2 _size;
	int _channels;
};
