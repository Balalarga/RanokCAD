#include "Window.h"
#include <format>
#include "spdlog/spdlog.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


std::unique_ptr<Window> Window::_gWindow;

WindowParams Window::_gParams{};

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

	glfwWindowHint(GLFW_VISIBLE, false);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, _gParams.opengl.version.x);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, _gParams.opengl.version.y);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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

	if (_gParams.vSync)
	{
		glfwSwapInterval(1);
	}

	BindGlfwCallbacks();
	ImGuiInit();
}

Window::~Window()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
}

void Window::SetParams(const WindowParams& params)
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
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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

void Window::ImGuiInit()
{
	constexpr const char* imguiGlslVersion = "#version 130";

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls}
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(_glfwWindow, true);
	ImGui_ImplOpenGL3_Init(imguiGlslVersion);
}

void Window::BeginImGuiFrame() const
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Window::EndImGuiFrame() const
{
	ImGui::Render();
}

const WindowParams& Window::GetParams() const
{
	return _gParams;
}

const glm::u16vec2& Window::GetSize() const
{
	return _size;
}

void Window::Hide()
{
	glfwHideWindow(_glfwWindow);
}

void Window::Show()
{
	glfwShowWindow(_glfwWindow);
}
