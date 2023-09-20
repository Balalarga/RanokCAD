#define IMGUI_DEFINE_MATH_OPERATORS
#include "DevelopmentModule.h"

#include "Graphics/RayMarchWidget.h"
#include "ImGui/imgui.h"
#include "Model/StandardModels.h"
#include "OpenglWrap/Core/Material.h"
#include "OpenglWrap/Core/SceneObject.h"
#include "OpenglWrap/Platform/InputManager.h"

DevelopmentModule::DevelopmentModule(glm::ivec2 windowSize, InputManager& inInputManager)
	: IModule(windowSize, inInputManager)
	, _viewport(std::make_shared<RayMarchWidget>(windowSize))
{
	InitInput();
	_viewport->Construct();

	auto part1 = std::make_unique<AssemblyPart>();
	part1->SetName("Part1");
	part1->SetColor({0.4, 0.1, 0.2, 1.0});
	part1->SetLocation({3, 0, 0});
	part1->SetFunctionTree(StandardModels::GetSphere());
	
	auto part2 = std::make_unique<AssemblyPart>();
	part2->SetName("Part2");
	part2->SetColor({0.1, 0.4, 0.2, 1.0});
	part2->SetLocation({0, 0, 3});
	part2->SetFunctionTree(StandardModels::GetSphere(2));
	
	auto part3 = std::make_unique<Assembly>();
	part3->SetName("Assembly1");
	
	auto part31 = std::make_unique<AssemblyPart>();
	part31->SetName("Part3");
	part31->SetColor({0.1, 0.2, 0.4, 1.0});
	part31->SetLocation({0, 3, 3});
	part31->SetFunctionTree(StandardModels::GetSphere(1));
	
	auto part32 = std::make_unique<AssemblyPart>();
	part32->SetName("Part4");
	part32->SetColor({0.2, 0.2, 0.3, 1.0});
	part32->SetLocation({0, 0, 6});
	part32->SetFunctionTree(StandardModels::GetSphere(1));
	
	part3->AddPart(std::move(part31));
	part3->AddPart(std::move(part32));
	
	_assembly.AddPart(std::move(part1));
	_assembly.AddPart(std::move(part2));
	_assembly.AddPart(std::move(part3));
	_viewport->SetObjects(_assembly);
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

void DevelopmentModule::InitInput() const
{
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

	inputManager.Add(
		SDL_SCANCODE_E,
		[&](Window&, const KeyState& state)
		{
			if (_bIsViewportFocused)
			{
				if (state == KeyState::Pressed || state == KeyState::Repeated)
				{
					_viewport->GetCamera().Move({0, 0.1, 0});
				}
			}
		});

	inputManager.Add(
		SDL_SCANCODE_Q,
		[&](Window&, const KeyState& state)
		{
			if (_bIsViewportFocused)
			{
				if (state == KeyState::Pressed || state == KeyState::Repeated)
				{
					_viewport->GetCamera().Move({0, -0.1, 0});
				}
			}
		});
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
	ImGui::BeginChild("##ModelTreeViewDetails", ImVec2(treeViewSizeMax.x, ImGui::GetItemRectSize().y - treeViewSizeMax.y));
	if (_assembly.DrawDetailsPanel())
	{
		_viewport->SetUniforms(_assembly);
	}
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
