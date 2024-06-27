#include "Window.h"
#include <format>
#include "spdlog/spdlog.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"


std::unique_ptr<Window> Window::_gWindow;

Window::Params Window::_gParams{
	.title = "Ranok3",
	.pos = {0, 0},
	.size = {800, 600},
	.fullscreen = false,
	.vSync = false,
	.opengl =
		{
			.version = {3, 3},
		},
};

void Window::GlfwErrorCallback(int error, const char* description)
{
	spdlog::error("[glfw3] [{}] {}", error, description);
}

Window& Window::Get()
{
	if (!_gWindow)
	{
		_gWindow = std::make_unique<Window>();
	}

	return *_gWindow;
}


Window::Window()
{
	if (!glfwInit())
	{
		spdlog::critical("Cannot initialize GLFW3");
		return;
	}
	glfwSetErrorCallback(&GlfwErrorCallback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, _gParams.opengl.version.x);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, _gParams.opengl.version.y);
	_glfwWindow = glfwCreateWindow(_gParams.size.x, _gParams.size.y, _gParams.title.c_str(), nullptr, nullptr);
	if (!_glfwWindow)
	{
		spdlog::critical("Cannot create window");
		return;
	}
	glfwMakeContextCurrent(_glfwWindow);

	if (auto error = glewInit(); error != GLEW_OK)
	{
		spdlog::critical("Cannot initialize GLEW: {}", (const char*)glewGetErrorString(error));
		return;
	}
}

Window::~Window()
{
	glfwTerminate();
}

void Window::SetParams(const Window::Params& params)
{
	_gParams = params;
}

bool Window::ShouldClose() const
{
	return glfwWindowShouldClose(_glfwWindow);
}
