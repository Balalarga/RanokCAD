#include "RanokCADApp.h"

#include "Core/RenderApi.h"
#include "imgui.h"

RanokCADApp::RanokCADApp() : Application({.renderRate = 165, .updateRate = 100}), widget({800, 600}, 3)
{
	GetInputManager()->Add(SDL_SCANCODE_ESCAPE, [](Window& window, const KeyState& state) { window.Close(); });
	widget.Init();
}

void RanokCADApp::Render()
{
	RenderApi::PushTarget(&widget);
	RenderApi::ClearColor({1.f, 1.f, 1.f, 1.f});
	RenderApi::PopTarget();

	Application::Render();
}

void RanokCADApp::RenderImGui()
{
	ImGui::Begin("Window");
	widget.DrawGui();
	ImGui::End();

	Application::RenderImGui();
}

void RanokCADApp::Update(float delta)
{
	Application::Update(delta);
}
