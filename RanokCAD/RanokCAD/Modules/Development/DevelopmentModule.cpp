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
			{
				_viewport->GetCamera().Rotate({state.moved.x / 20, 0 - state.moved.y / 20, 0});
			}
		});

	inputManager.Add(
		SDL_SCANCODE_W,
		[&](Window&, const KeyState& state)
		{
			if (_bIsViewportFocused)
			{
				if (state == KeyState::Pressed || state == KeyState::Repeated)
				{
					_viewport->GetCamera().Move({0, 0, 0.1});
				}
			}
		});

	inputManager.Add(
		SDL_SCANCODE_S,
		[&](Window&, const KeyState& state)
		{
			if (_bIsViewportFocused)
			{
				if (state == KeyState::Pressed || state == KeyState::Repeated)
				{
					_viewport->GetCamera().Move({0, 0, -0.1});
				}
			}
		});

	inputManager.Add(
		SDL_SCANCODE_D,
		[&](Window&, const KeyState& state)
		{
			if (_bIsViewportFocused)
			{
				if (state == KeyState::Pressed || state == KeyState::Repeated)
				{
					_viewport->GetCamera().Move({0.1, 0, 0});
				}
			}
		});

	inputManager.Add(
		SDL_SCANCODE_A,
		[&](Window&, const KeyState& state)
		{
			if (_bIsViewportFocused)
			{
				if (state == KeyState::Pressed || state == KeyState::Repeated)
				{
					_viewport->GetCamera().Move({-0.1, 0, 0});
				}
			}
		});

	auto part1 = std::make_unique<AssemblyPart>();
	part1->SetName("Part1");
	part1->SetColor({0.7, 0.1, 0.2, 1.0});
	auto part2 = std::make_unique<AssemblyPart>();
	part2->SetName("Part2");
	part1->SetColor({0.1, 0.7, 0.2, 1.0});

	part1->SetFunctionCode(R"(
def main(s[3])
{
	r = 1;
	return r^2 - (s[0]-3)^2.0 - s[1]^2.0 - (s[2] + 2)^2.0;
}
)");

	part2->SetFunctionCode(R"(
def s2()
{
	return 1;
}

def main(s[3])
{
	r = s2();
	return r^2 - s[0]^2 - s[1]^2.0 - s[2]^2.0;
}
)");

	
	_assembly.AddPart(std::move(part1));
	_assembly.AddPart(std::move(part2));
	_viewport->SetObjects(_assembly.Parts());
}

void DevelopmentModule::DrawMenuBar()
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New model"))
			{
			}
			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}
}

void DevelopmentModule::DrawGui()
{
	ImGui::Begin(
		"DevelopmentViewport",
		nullptr,
		ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_MenuBar);

	DrawMenuBar();
	DrawToolBar();
	DrawViewport();

	ImGui::End();
}

void DevelopmentModule::DrawViewport()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

	ImGui::BeginChild("##DevRightPanel", ImGui::GetContentRegionAvail(), true, ImGuiWindowFlags_NoScrollbar);
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
	_viewport->DrawGui();
	ImGui::PopStyleVar(); // ImGuiStyleVar_FramePadding
	DrawTreeView();
	_bIsViewportFocused = ImGui::IsWindowFocused() || ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup);
	ImGui::EndChild();

	ImGui::PopStyleVar(); // ImGuiStyleVar_WindowPadding
}

void DevelopmentModule::DrawTreeView()
{
	ImVec2 treeViewSizeMax = ImGui::GetItemRectSize();
	treeViewSizeMax.x /= 4;
	treeViewSizeMax.y /= 2;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(6, 6));
	ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, 10);

	ImGui::SetCursorPos(ImGui::GetStyle().WindowPadding);

	ImGui::BeginChild("##ModelTreeView", treeViewSizeMax);
	_assembly.DrawGui();
	ImGui::EndChild();

	ImGui::PopStyleVar(2);
}

void DevelopmentModule::DrawToolBar()
{
	ImGui::BeginGroup();

	if (ImGui::Button("ModelPicker"))
	{
		// ModelItem newItem = ModelItem().SetName("NewItem");
		// _modelTree.Add(ModelTree(newItem));
	}

	ImGui::EndGroup();
}
