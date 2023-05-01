#include "FboWidget.h"

#include "ImGui/imgui.h"

FboWidget::~FboWidget()
{
	FboWidget::Destroy();
}

bool FboWidget::SetRenderingTexture(int type)
{
	if (!GetTexture(type))
		return false;

	_textureDrawType = type;
	return true;
}

void FboWidget::DrawGui()
{
	if (Texture* texture = GetTexture(_textureDrawType))
		ImGui::Image((void*)texture->GetHandle(), ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0));
}

void FboWidget::Bind()
{
	FrameBuffer::Bind();
	if (!_renderingBuffers.empty())
		glDrawBuffers(static_cast<int>(_renderingBuffers.size()), _renderingBuffers.data());
}
