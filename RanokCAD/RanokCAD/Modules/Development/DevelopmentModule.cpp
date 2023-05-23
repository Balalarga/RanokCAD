#include "DevelopmentModule.h"
#define IMGUI_DEFINE_MATH_OPERATORS

#include "ImGui/imgui.h"
#include "OpenglWrap/Core/Material.h"
#include "OpenglWrap/Core/SceneObject.h"
#include "OpenglWrap/Platform/InputManager.h"
#include "RanokCAD/Graphics/RayMarchWidget.h"

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

	_modelTree.AddModel(ModelTreeInfo("Circle1"));
	_modelTree.AddModel(ModelTreeInfo("Circle2"));
}

void DevelopmentModule::DrawGui()
{
	static float splitterPosX = ImGui::GetWindowContentRegionMax().x / 3.f;
	ImGui::Begin("DevelopmentViewport");
	ImGui::BeginChild("##MainZone");
	// ImGui::BeginChild("##TextEditorChild", ImVec2(splitterPosX, 0), true, ImGuiWindowFlags_NoScrollbar);
	// _modelTree.DrawGui();
	// ImGui::EndChild();
	// ImGui::SameLine();

	ImGui::InvisibleButton("##VSplitter", ImVec2(5.0f, ImGui::GetWindowContentRegionMax().y));
	const bool bIsActive = ImGui::IsItemActive();
	const bool bIsHovered = ImGui::IsItemHovered();
	if (bIsActive)
		splitterPosX += ImGui::GetIO().MouseDelta.x;
	if (bIsActive || bIsHovered)
		ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);
	ImGui::SameLine();

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::BeginChild("##Viewport", ImGui::GetContentRegionAvail(), true, ImGuiWindowFlags_NoScrollbar);
	_viewport->DrawGui();

	ImGui::SetItemAllowOverlap();
	ImGui::SetCursorPos(ImGui::GetWindowContentRegionMin());

	ImGui::BeginChild(
		"##TreeModel", ImVec2(ImGui::GetContentRegionAvail().x / 6.f, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
	bool isHidden = !ImGui::IsWindowHovered(); // TODO: Change to mouse position
	if (isHidden)
		ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyle().Colors[ImGuiCol_Text] * ImVec4(1.0f, 1.0f, 1.0f, 0.3f));

	_modelTree.DrawGui();

	if (isHidden)
		ImGui::PopStyleColor();

	ImGui::EndChild();

	ImGui::EndChild();

	ImGui::PopStyleVar();
	ImGui::EndChild();

	ImGui::End();
}
