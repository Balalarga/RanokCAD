#define IMGUI_DEFINE_MATH_OPERATORS
#include "DevelopmentModule.h"

#include "ImGui/imgui.h"
#include "OpenglWrap/Core/Material.h"
#include "OpenglWrap/Core/SceneObject.h"
#include "OpenglWrap/Platform/InputManager.h"
#include "Graphics/RayMarchWidget.h"

DevelopmentModule::DevelopmentModule(InputManager& inInputManager) :
	IModule(inInputManager), _viewport(std::make_shared<RayMarchWidget>(glm::ivec2{800, 600}))
{
	_viewport->Construct();
	inputManager.AddOnMouseMove(
		[&](Window&, const MouseState& state)
		{
			if (state.keys[static_cast<int>(MouseKey::Right)] == KeyState::Pressed)
			{
				_viewport->GetCamera().Rotate({-state.moved.y / 10.f, state.moved.x / 10.f, 0});
			}
		});

	inputManager.Add(SDL_SCANCODE_W,
					 [&](Window&, const KeyState& state)
					 {
						 if (state == KeyState::Pressed || state == KeyState::Repeated)
						 {
							 _viewport->GetCamera().Move({0, 0, 0.1});
						 }
					 });

	inputManager.Add(SDL_SCANCODE_S,
					 [&](Window&, const KeyState& state)
					 {
						 if (state == KeyState::Pressed || state == KeyState::Repeated)
						 {
							 _viewport->GetCamera().Move({0, 0, -0.1});
						 }
					 });

	inputManager.Add(SDL_SCANCODE_D,
					 [&](Window&, const KeyState& state)
					 {
						 if (state == KeyState::Pressed || state == KeyState::Repeated)
						 {
							 _viewport->GetCamera().Move({0.1, 0, 0});
						 }
					 });

	inputManager.Add(SDL_SCANCODE_A,
					 [&](Window&, const KeyState& state)
					 {
						 if (state == KeyState::Pressed || state == KeyState::Repeated)
						 {
							 _viewport->GetCamera().Move({-0.1, 0, 0});
						 }
					 });
}

void DevelopmentModule::DrawGui()
{
	ImGui::Begin("DevelopmentViewport");
	static float splitterPosX = ImGui::GetWindowContentRegionMax().x / 5.f;
	ImGui::BeginChild("##MainZone");
	DrawLeftPanel(ImVec2(splitterPosX, 0));
	ImGui::SameLine();

	ImGui::InvisibleButton("##VSplitter", ImVec2(5.0f, ImGui::GetWindowContentRegionMax().y));
	const bool bIsActive = ImGui::IsItemActive();
	const bool bIsHovered = ImGui::IsItemHovered();
	if (bIsActive)
		splitterPosX += ImGui::GetIO().MouseDelta.x;
	if (bIsActive || bIsHovered)
		ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);
	ImGui::SameLine();

	DrawRightPanel();

	ImGui::EndChild();
	ImGui::End();
}

void DevelopmentModule::DrawRightPanel()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

	ImGui::BeginChild("##DevRightPanel", ImGui::GetContentRegionAvail(), true, ImGuiWindowFlags_NoScrollbar);
	_viewport->DrawGui();
	DrawTreeView();
	ImGui::EndChild();

	ImGui::PopStyleVar(); // ImGuiStyleVar_WindowPadding
}

void DevelopmentModule::DrawTreeView()
{
	const ImVec2 treeViewSizeMin = ImGui::GetItemRectSize() / ImVec2(6, 3);
	const ImVec2 treeViewSizeMax = ImGui::GetItemRectSize() / ImVec2(3, 1.5f);
	static bool bIsHovered = false;

	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImGui::GetStyle().Colors[ImGuiCol_WindowBg] * ImVec4(1, 1, 1, 0.4f));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(6, 6));
	ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, 10);
	if (bIsHovered)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 1);
	}
	else
	{
		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.6f);
	}

	ImGui::SetNextWindowPos(ImGui::GetWindowPos() + ImGui::GetStyle().WindowPadding);
	ImGui::SetNextWindowSizeConstraints(treeViewSizeMin, treeViewSizeMax);

	ImGui::Begin("##TreeModel",
				 nullptr,
				 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_HorizontalScrollbar);

	_modelTree.DrawGui();
	bIsHovered = ImGui::IsAnyItemHovered() ||
		ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup | ImGuiHoveredFlags_RootAndChildWindows);
	ImGui::End();

	ImGui::PopStyleVar(3);
	ImGui::PopStyleColor(); // ImGuiCol_WindowBg
}

void DevelopmentModule::DrawLeftPanel(const ImVec2& size)
{
	ImGui::BeginChild("##ModelsPicker", size, true);
	if (ImGui::BeginTabBar("##DevLeftPanel"))
	{
		if (ImGui::BeginTabItem("Models"))
		{
			ImGui::Button("ModelPicker");
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
	ImGui::EndChild();
}
