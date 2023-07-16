#pragma once
#include <imgui.h>



class ImGuiWidgets
{
public:
	ImGuiWidgets() = delete;
	ImGuiWidgets(ImGuiWidgets&&) = delete;
	ImGuiWidgets(const ImGuiWidgets&) = delete;

	static void ResizableVSplitter(
		float& splitterPosX,
		const ImVec2& size = { 5.f, ImGui::GetWindowContentRegionMax().y },
		const char* label = "##VSplitter");

	static void ResizableHSplitter(
		float& splitterPosY,
		const ImVec2& size = { ImGui::GetWindowContentRegionMax().x, 5.f },
		const char* label = "##HSplitter");
};
