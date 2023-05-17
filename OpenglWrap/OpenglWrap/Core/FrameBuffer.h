#pragma once
#include <map>
#include <vector>

#include "RenderTarget.h"
#include "Texture.h"

class FrameBuffer: public VramHandle, public RenderTarget
{
public:
	FrameBuffer(glm::ivec2 _size);
	virtual ~FrameBuffer();

	void Bind() override;
	void Release() override;
	void Present() override;

	bool IsValid() const override;

	glm::ivec2 GetSize() const
	{
		return _size;
	}

	Texture* GetTexture(int type);

	template<class... TArgs>
	Texture* AddTexture(int type, TArgs&&... args)
	{
		if (auto texture = GetTexture(type))
			return texture;

		const auto it = _textures.try_emplace(type, std::forward<TArgs>(args)...);
		if (IsValid())
			glFramebufferTexture2D(GL_FRAMEBUFFER, type, GL_TEXTURE_2D, it.first->second.GetHandle(), 0);

		return &it.first->second;
	}

	void SetRenderingBuffers(const std::vector<GLenum>& buffers)
	{
		_renderingBuffers = buffers;
	}

	const std::vector<GLenum>& GetRenderingBuffers() const
	{
		return _renderingBuffers;
	}


protected:
	bool PreInit() override;
	bool Init() override;

	int AllocateVram() override;
	void DeallocateVram() override;

	std::map<int, Texture>& Textures()
	{
		return _textures;
	}


private:
	std::vector<GLenum> _renderingBuffers;
	glm::ivec2 _size;
	std::map<int, Texture> _textures;
};
