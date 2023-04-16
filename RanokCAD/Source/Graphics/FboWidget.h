#pragma once
#include "Core/FrameBuffer.h"
#include "ImGuiWidget.h"

class FboWidget: public FrameBuffer, public ImGuiWidget
{
public:
	using FrameBuffer::FrameBuffer;

	void DrawGui() override;
};
