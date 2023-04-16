#include "FboWidget.h"

#include "imgui.h"

void FboWidget::DrawGui()
{
	ImGui::GetWindowDrawList()->AddImage((void*)GetTexture().GetHandle(),
										 ImGui::GetCursorScreenPos(),
										 ImVec2(ImGui::GetCursorScreenPos().x + ImGui::GetContentRegionAvail().x,
												ImGui::GetCursorScreenPos().y + ImGui::GetContentRegionAvail().y),
										 ImVec2(0, 1),
										 ImVec2(1, 0));
}