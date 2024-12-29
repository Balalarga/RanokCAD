#include "Application.h"
#include <thread>
#include <utility>

#include "imgui.h"
#include "spdlog/spdlog.h"


Application::Application(AppParams params) : _params(std::move(params)), _window(_params.windowParams) {
}

void Application::Launch() {
	_window.Show();
	MainLoop();
}

void Application::MainLoop() {
	const double targetFrameMs = _params.fps != 0 ? 1000. / _params.fps : 0;
	double frameTime = 1;
	while (!_window.ShouldClose()) {
		const auto frameStart = glfwGetTime();

		_window.HandleEvents();

		Update(frameTime);

		_window.BeginImGuiFrame();
		RenderImGui();
		_window.EndImGuiFrame();
		Render();
		_window.SwapBuffers();

		frameTime = 1000. * (glfwGetTime() - frameStart);
		if (!_window.GetParams().vSync && frameTime < targetFrameMs) {
			const auto sleepMs = static_cast<int>(std::round(targetFrameMs - frameTime));
			std::this_thread::sleep_for(std::chrono::milliseconds(sleepMs));
			frameTime = targetFrameMs;
		}
	}
}

void Application::Render() {
	glViewport(0, 0, _window.GetSize().x, _window.GetSize().y);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Application::Update(double dt) {
}

void Application::RenderImGui() {
	ImGui::ShowDemoWindow();
}