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

Window& Window::Get()
{
	if (!_gWindow)
	{
		_gWindow = std::make_unique<Window>();
	}

	return *_gWindow;
}


Window::Window()
	: _size(_gParams.size)
{
	if (!glfwInit())
	{
		spdlog::critical("Cannot initialize GLFW3");
		return;
	}

	glfwSetErrorCallback([](int error, const char* description)
						 { spdlog::error("[glfw3] [{}] {}", error, description); });

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, _gParams.opengl.version.x);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, _gParams.opengl.version.y);
	_glfwWindow = glfwCreateWindow(_size.x, _size.y, _gParams.title.c_str(), nullptr, nullptr);
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

	glfwSwapInterval(1);
	BindGlfwCallbacks();
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

void Window::HandleEvents() const
{
	glfwPollEvents();
}

void Window::SwapBuffers() const
{
	glfwSwapBuffers(_glfwWindow);
}

void Window::Close()
{
	glfwSetWindowShouldClose(_glfwWindow, true);
}

void Window::GlfwWindowChangeSizeEvent(int width, int height)
{
	_size.x = width;
	_size.y = height;
}

void Window::GlfwMouseMoveEvent(double xpos, double ypos)
{
}

void Window::GlfwMouseButtonEvent(int button, int action, int mods)
{
}

void Window::GlfwKeyboardButtonEvent(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		Close();
}

void Window::BindGlfwCallbacks()
{
	glfwSetWindowSizeCallback(
		_glfwWindow,
		[](GLFWwindow* window, int width, int height)
		{
			if (Get()._glfwWindow != window)
				return;
			Get().GlfwWindowChangeSizeEvent(width, height);
		});
	glfwSetCursorPosCallback(
		_glfwWindow,
		[](GLFWwindow* window, double xpos, double ypos)
		{
			if (Get()._glfwWindow != window)
				return;
			Get().GlfwMouseMoveEvent(xpos, ypos);
		});
	glfwSetMouseButtonCallback(
		_glfwWindow,
		[](GLFWwindow* window, int button, int action, int mods)
		{
			if (Get()._glfwWindow != window)
				return;
			Get().GlfwMouseButtonEvent(button, action, mods);
		});
	glfwSetKeyCallback(
		_glfwWindow,
		[](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (Get()._glfwWindow != window)
				return;

			Get().GlfwKeyboardButtonEvent(key, scancode, action, mods);
		});
}
