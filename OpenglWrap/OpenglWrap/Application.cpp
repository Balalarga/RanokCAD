#include "Application.h"
#include <chrono>
#include "Core/RenderApi.h"
#include "ImGui/backends/imgui_impl_opengl3.h"
#include "ImGui/backends/imgui_impl_sdl2.h"


Application::Application(Params params) :
	_params(std::move(params)), _window(std::make_unique<Window>(_params.windowInitializer)),
	_inputManager(std::make_unique<InputManager>(*_window))
{
	if (_params.updateRate <= 0)
		_params.updateRate = 1;

	if (_params.renderRate <= 0)
		_params.renderRate = 1;
}

void Application::Run()
{
	using namespace std::chrono;


	size_t updateTimeMcs = 1000000 / _params.updateRate;
	size_t renderTimeMcs = 1000000 / _params.renderRate;
	size_t updateTimerMcs = 0;


	_window->Open(); // Enforce window opening
	while (_window->IsOpen())
	{
		high_resolution_clock::time_point frameStart = high_resolution_clock::now();

		// Event handling
		_inputManager->HandleEvent();

		// Updating
		if (updateTimerMcs >= updateTimeMcs)
		{
			Update(static_cast<float>(updateTimeMcs) / 1000.f);
			updateTimerMcs -= updateTimeMcs;
		}

		// Rendering
		RenderApi::Clear();
		Render();

		// ImGui Rendering
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
		RenderImGui();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		RenderApi::Present();

		// Frame delay
		high_resolution_clock::time_point frameEnd = high_resolution_clock::now();
		long long duration = duration_cast<microseconds>(frameEnd - frameStart).count();
		if (duration < renderTimeMcs)
		{
			SDL_Delay(static_cast<uint32_t>((renderTimeMcs - duration) / 1000));
			duration = renderTimeMcs;
		}
		updateTimerMcs += duration;
	}
}

void Application::Render()
{
	if (_onRenderEvent)
		_onRenderEvent();
}

void Application::RenderImGui()
{
	if (_onImGuiRenderEvent)
		_onImGuiRenderEvent();
}

void Application::Update(float delta)
{
	if (_onUpdateEvent)
		_onUpdateEvent(delta);
}

void Application::SetOnRenderEvent(const std::function<void()>& func)
{
	_onRenderEvent = func;
}

void Application::SetOnImGuiRenderEvent(const std::function<void()>& func)
{
	_onImGuiRenderEvent = func;
}

void Application::SetOnUpdateEvent(const std::function<void(float)>& func)
{
	_onUpdateEvent = func;
}
