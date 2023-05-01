#include "Application.h"

#include <chrono>

#include "Core/RenderApi.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl2.h"

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
	long long updateTimeMcs = 1000000 / _params.updateRate;
	long long renderTimeMcs = 1000000 / _params.renderRate;
	long long updateTimerMcs = 0;

	_window->Open();
	while (_window->IsOpen())
	{
		high_resolution_clock::time_point frameStart = high_resolution_clock::now();
		_inputManager->HandleEvent();

		if (updateTimerMcs >= updateTimeMcs)
		{
			Update(static_cast<float>(updateTimeMcs) / 1000.f);
			updateTimerMcs -= updateTimeMcs;
		}
		RenderApi::Clear();

		Render();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		RenderImGui();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		RenderApi::Present();

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
	if (_onRender)
		_onRender();
}

void Application::RenderImGui()
{
	if (_onImGuiRender)
		_onImGuiRender();
}

void Application::Update(float delta)
{
	if (_onUpdate)
		_onUpdate(delta);
}

void Application::SetOnRender(const std::function<void()>& func)
{
	_onRender = func;
}

void Application::SetOnImGuiRender(const std::function<void()>& func)
{
	_onImGuiRender = func;
}

void Application::SetOnUpdate(const std::function<void(float)>& func)
{
	_onUpdate = func;
}
