#include "Application.h"
#include <thread>
#include "../Window/Window.h"
#include "imgui.h"
#include "spdlog/spdlog.h"


Application::Application(Window& window, const AppParams& params)
	: _params(params)
	, _window(window)
{
	NormalizeParams();
}

void Application::RunLoop()
{
	using clock = std::chrono::system_clock;

	const clock::duration targetFrameTime(1. / _params.fps);
	const clock::duration targetUpdateTime(clock::duration(1. / _params.ups);
	clock::duration frameTime;
	clock::duration updateTime;

	while (!_window.ShouldClose())
	{
		const auto frameStart = std::chrono::system_clock::now();

		_window.HandleEvents();

		updateTime += frameTime;
		if (updateTime >= targetUpdateTime)
		{
			Update(updateTime);
			updateTime = 0;
		}

		_window.BeginImGuiFrame();
		ImGui::ShowDemoWindow();
		_window.EndImGuiFrame();

		Render();
		_window.SwapBuffers();

		std::chrono::system_clock::duration frameTime = std::chrono::system_clock::now() - frameStart;
		if (frameTime < targetFrameTime)
		{
			auto sleepMs = static_cast<int>(std::round(targetFrameTime - frameTime));
			std::this_thread::sleep_for(std::chrono::milliseconds(sleepMs));
			frameTime = targetFrameTime;
		}
	}
}

void Application::NormalizeParams()
{
	if (_params.fps == 0)
	{
		_params.fps = 1;
		spdlog::error("Fps cannot be 0");
	}

	if (_params.ups == 0)
	{
		_params.ups = 1;
		spdlog::error("Ups cannot be 0");
	}
}

void Application::Render()
{
	glViewport(0, 0, _window.GetSize().x, _window.GetSize().y);
}

void Application::Update(double dt)
{
}
