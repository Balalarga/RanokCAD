#pragma once
#include <vector>

#include "ImGuiWidget.h"
#include "OpenglWrap/Core/FrameBuffer.h"

class FboWidget: public FrameBuffer, public ImGuiWidget
{
public:
	using FrameBuffer::FrameBuffer;
	virtual ~FboWidget();

	bool SetRenderingTexture(int type);

	void DrawGui() override;

	template<class... TArgs>
	bool AddRenderingTexture(int type, TArgs&&... args)
	{
		if (!AddTexture(type, std::forward<TArgs>(args)...))
			return false;

		_textureDrawType = type;
		return true;
	}


private:
	int _textureDrawType = GL_MAX_COLOR_ATTACHMENTS;
};
