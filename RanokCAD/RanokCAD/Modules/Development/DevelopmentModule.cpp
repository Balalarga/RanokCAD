#define IMGUI_DEFINE_MATH_OPERATORS

#include "DevelopmentModule.h"

#include "Graphics/RayMarchWidget.h"
#include "ImGui/imgui.h"
#include "OpenglWrap/Core/Material.h"
#include "OpenglWrap/Core/SceneObject.h"
#include "OpenglWrap/Platform/InputManager.h"


DevelopmentModule::DevelopmentModule(glm::ivec2 windowSize, InputManager& inInputManager)
	: IModule(windowSize, inInputManager)
	, _viewport(std::make_shared<RayMarchWidget>(windowSize))
{
	_viewport->Construct();
	inputManager.AddOnMouseMove(
		[&](Window&, const MouseState& state)
		{
			if (state.keys[static_cast<uint8_t>(MouseKey::Right)] == KeyState::Pressed)
				_viewport->GetCamera().Rotate({ -state.moved.y / 10.f, state.moved.x / 10.f, 0 });
		});

	inputManager.Add(
		SDL_SCANCODE_W,
		[&](Window&, const KeyState& state)
		{
			if (state == KeyState::Pressed || state == KeyState::Repeated)
				_viewport->GetCamera().Move({ 0, 0, 0.1 });
		});

	inputManager.Add(
		SDL_SCANCODE_S,
		[&](Window&, const KeyState& state)
		{
			if (state == KeyState::Pressed || state == KeyState::Repeated)
				_viewport->GetCamera().Move({ 0, 0, -0.1 });
		});

	inputManager.Add(
		SDL_SCANCODE_D,
		[&](Window&, const KeyState& state)
		{
			if (state == KeyState::Pressed || state == KeyState::Repeated)
				_viewport->GetCamera().Move({ 0.1, 0, 0 });
		});

	inputManager.Add(
		SDL_SCANCODE_A,
		[&](Window&, const KeyState& state)
		{
			if (state == KeyState::Pressed || state == KeyState::Repeated)
				_viewport->GetCamera().Move({ -0.1, 0, 0 });
		});
}

void DevelopmentModule::DrawGui()
{
	ImGui::Begin("DevelopmentViewport", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration);

	ImGui::BeginGroup();
	DrawControls();
	ImGui::EndGroup();

	DrawViewport();
	ImGui::End();
}

void DevelopmentModule::DrawViewport()
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
	ImVec2 treeViewSizeMax = ImGui::GetItemRectSize();
	treeViewSizeMax.x /= 3;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(6, 6));
	ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, 10);

	ImGui::SetCursorPos(ImGui::GetStyle().WindowPadding);

	ImGui::BeginChild("##ModelTreeView", treeViewSizeMax);

	_modelTree.DrawGui();

	ImGui::EndChild();

	ImGui::PopStyleVar(2);
}

void DevelopmentModule::DrawControls()
{
	ImGui::Button("ModelPicker");
}
