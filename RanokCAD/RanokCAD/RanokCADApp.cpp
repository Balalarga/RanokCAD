#include "RanokCADApp.h"

#include "Graphics/RayMarchWidget.h"
#include "ImGui/imgui.h"
#include "Modules/DevelopmentModule.h"

RanokCADApp::RanokCADApp() :
	Application({.renderRate = 165,
				 .updateRate = 100,
				 .windowInitializer = {.Flags = Window::sWindowDefaultFlags | SDL_WINDOW_RESIZABLE}}),
	_activeModule(std::make_shared<DevelopmentModule>())
{
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	GetInputManager()->Add(SDL_SCANCODE_ESCAPE, [](Window& window, const KeyState& state) { window.Close(); });
}

void RanokCADApp::RenderImGui()
{
	ImGui::DockSpaceOverViewport();

	if (_activeModule)
		_activeModule->DrawGui();

	Application::RenderImGui();
}
