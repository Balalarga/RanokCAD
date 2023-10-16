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
	{
		Model part1("Part11");
		part1.SetColor({0.1, 0.2, 0.4, 1.0});
		part1.SetLocation({0, -3, -3});
		part1.SetFunctionTree(StandardModels::GetSphere(1));

		Model part2("Part12");
		part2.SetColor({0.1, 0.2, 0.4, 1.0});
		part2.SetLocation({0, 0, -6});
		part2.SetFunctionTree(StandardModels::GetSphere(1));

		Model part3("Part13");
		part3.SetColor({0.3, 0.3, 0.3, 1.0});
		part3.SetLocation({0, -1, -1});
		part3.SetFunctionTree(StandardModels::GetSphere(1));
	
		Assembly assembly("Assembly1");
		assembly.SetLocation({0, 0, 0});
		assembly.SetColor({0.2, 0.2, 0.3, 1.0});
		assembly.AddPart(AssemblyPart(part1, AssemblyPart::CombineType::Union));
		assembly.AddPart(AssemblyPart(part3, AssemblyPart::CombineType::Union));
		assembly.AddPart(AssemblyPart(part2, AssemblyPart::CombineType::Union));
		_assemblies.emplace_back(assembly);
	}
	{
		Model part1("Part21");
		part1.SetColor({0.1, 0.2, 0.4, 1.0});
		part1.SetLocation({0, 3, 3});
		part1.SetFunctionTree(StandardModels::GetSphere(1));

		Model part2("Part22");
		part2.SetColor({0.1, 0.2, 0.4, 1.0});
		part2.SetLocation({0, 3, 0});
		part2.SetFunctionTree(StandardModels::GetSphere(1));

		Model part3("Part23");
		part3.SetColor({0.3, 0.3, 0.3, 1.0});
		part3.SetLocation({0, 1, 1});
		part3.SetFunctionTree(StandardModels::GetSphere(1));
	
		Assembly assembly("Assembly2");
		assembly.SetColor({0.4, 0.2, 0.2, 1.0});
		assembly.AddPart(AssemblyPart(part1, AssemblyPart::CombineType::Union));
		assembly.AddPart(AssemblyPart(part3, AssemblyPart::CombineType::Union));
		assembly.AddPart(AssemblyPart(part2, AssemblyPart::CombineType::Union));
		_assemblies.emplace_back(assembly);
	}

	_viewport->SetObjects(_assemblies);
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
	static IModelBase* selectedItem = nullptr;
	for (Assembly& assembly : _assemblies)
	{
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
		if (selectedItem == &assembly)
			flags |= ImGuiTreeNodeFlags_Selected;

		const bool bAssemblyOpened = ImGui::TreeNodeEx(assembly.GetName().c_str(), flags);
		
		if (ImGui::IsItemClicked())
			selectedItem = &assembly;

		if (!bAssemblyOpened)
			continue;
		
		for (AssemblyPart& part : assembly.GetParts())
		{
			ImGuiTreeNodeFlags partFlags = ImGuiTreeNodeFlags_Leaf;
			if (selectedItem == &part.model)
				partFlags |= ImGuiTreeNodeFlags_Selected;

			const bool bPartOpened = ImGui::TreeNodeEx(part.model.GetName().c_str(), partFlags);
			if (ImGui::IsItemClicked())
				selectedItem = &part.model;
			
			if (!bPartOpened)
				continue;
			
			ImGui::TreePop();
		}
		ImGui::TreePop();
	}
	ImGui::EndChild();
	ImGui::BeginChild(
		"##ModelTreeViewDetails",
		ImVec2(treeViewSizeMax.x, ImGui::GetItemRectSize().y - treeViewSizeMax.y));
	ImGui::BeginGroup();

	static glm::fvec3 location;
	if (selectedItem)
	{
		location = selectedItem->GetLocation();
		if (ImGui::DragFloat3("Location", &location.x) && location != selectedItem->GetLocation())
		{
			selectedItem->SetLocation(location);
			_viewport->SetObjects(_assemblies);
		}
	}
	ImGui::EndGroup();
	ImGui::EndChild();
	ImGui::PopStyleVar(2);
}

void DevelopmentModule::DrawToolBar()
{
	ImGui::BeginGroup();

	if (ImGui::Button("Sphere"))
	{
		Model part31("NewPart");
		part31.SetColor({0.3, 0.3, 0.3, 1.0});
		part31.SetLocation({0, 5, 5});
		part31.SetFunctionTree(StandardModels::GetSphere(1));
		_assemblies.back().AddPart(AssemblyPart{part31, AssemblyPart::CombineType::Union});
		_viewport->SetObjects(_assemblies);
	}

	ImGui::EndGroup();
}
