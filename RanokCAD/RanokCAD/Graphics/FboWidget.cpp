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
		ImGui::Image((void*)texture->GetHandle(), ImGui::GetWindowSize(), ImVec2(0, 1), ImVec2(1, 0));
}
