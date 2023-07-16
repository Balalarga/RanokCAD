#include "ImGuiWidgets.h"


void ImGuiWidgets::ResizableVSplitter(float& splitterPosX, const ImVec2& size, const char* label)
{
	ImGui::InvisibleButton(label, size);
	const bool bIsActive = ImGui::IsItemActive();

	if (bIsActive || ImGui::IsItemHovered())
		ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);

	if (bIsActive)
		splitterPosX += ImGui::GetIO().MouseDelta.x;
}

void ImGuiWidgets::ResizableHSplitter(float& splitterPosY, const ImVec2& size, const char* label)
{
	ImGui::InvisibleButton(label, size);
	const bool bIsActive = ImGui::IsItemActive();

	if (bIsActive || ImGui::IsItemHovered())
		ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNS);

	if (bIsActive)
		splitterPosY += ImGui::GetIO().MouseDelta.y;
}
