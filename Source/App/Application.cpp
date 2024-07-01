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
	const double targetFrameMs = 1000. / _params.fps;
	double frameTime;

	while (!_window.ShouldClose())
	{
		const auto frameStart = glfwGetTime();

		_window.HandleEvents();

		Update(frameTime);

		_window.BeginImGuiFrame();
		RenderImGui();
		_window.EndImGuiFrame();

		Render();
		_window.SwapBuffers();

		frameTime = 1000. * (glfwGetTime() - frameStart);
		if (!_window.GetParams().vSync && frameTime < targetFrameMs)
		{
			auto sleepMs = static_cast<int>(std::round(targetFrameMs - frameTime));
			std::this_thread::sleep_for(std::chrono::milliseconds(sleepMs));
			frameTime = targetFrameMs;
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

	if (_window.GetParams().vSync)
	{
		_params.fps = 1;
	}
}

void Application::Render()
{
	glViewport(0, 0, _window.GetSize().x, _window.GetSize().y);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Application::Update(double dt)
{
	if (std::fabs(dt) <= std::numeric_limits<double>::epsilon())
		return;
}

void Application::RenderImGui()
{
}
