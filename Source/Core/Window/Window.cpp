#include "Window.h"
#include "spdlog/spdlog.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


void to_json(nlohmann::json& j, const WindowParams& p) {
	j["title"] = p.title;
	j["pos"] = { p.pos.x, p.pos.y };
	j["size"] = { p.size.x, p.size.y };
	j["fullscreen"] = p.fullscreen;
	j["vSync"] = p.vSync;
}

void from_json(const nlohmann::json& j, WindowParams& p) {
	p.title = j["title"];
	p.pos = { j["pos"][0].get<glm::u16>(), j["pos"][1].get<glm::u16>() };
	p.size = { j["size"][0].get<glm::u16>(), j["size"][1].get<glm::u16>() };
	p.fullscreen = j["fullscreen"];
	p.vSync = j["vSync"];
}

Window::Window(WindowParams params): _params(std::move(params)) {
	GlfwInit();
	ImGuiInit();
}

Window::~Window() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
}

void Window::SetParams(const WindowParams& params) {
	_params = params;
}

bool Window::ShouldClose() const {
	return glfwWindowShouldClose(_glfwWindow);
}

void Window::HandleEvents() const {
	(void*)(this);
	glfwPollEvents();
}

void Window::SwapBuffers() const {
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(_glfwWindow);
}

Window* Window::GetWindow(GLFWwindow* glfwWindow) {
	auto window = glfwGetWindowUserPointer(glfwWindow);
	assert(window);
	if (window)
		return static_cast<Window*>(window);
	return nullptr;
}

void Window::Close() const {
	glfwSetWindowShouldClose(_glfwWindow, true);
}

void Window::GlfwWindowChangeSizeEvent(int width, int height) {
	spdlog::info("Resize");
	_params.size.x = width;
	_params.size.y = height;
}

void Window::GlfwMouseMoveEvent(double xpos, double ypos) {
	(void*)(this);
}

void Window::GlfwMouseButtonEvent(int button, int action, int mods) {
	(void*)(this);
}

void Window::GlfwKeyboardButtonEvent(int key, int scancode, int action, int mods) {
	static_cast<void*>(this);
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		Close();
}

void Window::BindGlfwCallbacks() const {
	glfwSetWindowSizeCallback(
		_glfwWindow,
		[](GLFWwindow* window, int width, int height) {
			const auto self = GetWindow(window);
			if (!self)
				return;

			self->GlfwWindowChangeSizeEvent(width, height);
		});

	glfwSetCursorPosCallback(
		_glfwWindow,
		[](GLFWwindow* window, double xpos, double ypos) {
			const auto self = GetWindow(window);
			if (!self)
				return;

			self->GlfwMouseMoveEvent(xpos, ypos);
		});
	glfwSetMouseButtonCallback(
		_glfwWindow,
		[](GLFWwindow* window, int button, int action, int mods) {
			const auto self = GetWindow(window);
			if (!self)
				return;

			self->GlfwMouseButtonEvent(button, action, mods);
		});
	glfwSetKeyCallback(
		_glfwWindow,
		[](GLFWwindow* window, int key, int scancode, int action, int mods) {
			const auto self = GetWindow(window);
			if (!self)
				return;

			self->GlfwKeyboardButtonEvent(key, scancode, action, mods);
		});
}

void Window::ImGuiInit() {
	constexpr const char* imguiGlslVersion = "#version 130";

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;// Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls}
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(_glfwWindow, true);
	ImGui_ImplOpenGL3_Init(imguiGlslVersion);
}

void Window::GlfwInit() {
	if (!glfwInit()) {
		spdlog::critical("Cannot initialize GLFW3");
		return;
	}

	glfwSetErrorCallback(
		[](int error, const char* description) { spdlog::error("[glfw3] [{}] {}", error, description); });

	glfwWindowHint(GLFW_VISIBLE, false);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, _params.opengl.version.x);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, _params.opengl.version.y);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	_glfwWindow = glfwCreateWindow(_params.size.x, _params.size.y, _params.title.c_str(), nullptr, nullptr);
	if (!_glfwWindow) {
		spdlog::critical("Cannot create window");
		return;
	}
	glfwSetWindowUserPointer(_glfwWindow, this);
	glfwMakeContextCurrent(_glfwWindow);

	if (auto error = glewInit(); error != GLEW_OK) {
		spdlog::critical("Cannot initialize GLEW: {}", reinterpret_cast<const char*>(glewGetErrorString(error)));
		return;
	}

	if (_params.vSync) {
		glfwSwapInterval(1);
	}

	BindGlfwCallbacks();
}

void Window::BeginImGuiFrame() const {
	(void*)(this);
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Window::EndImGuiFrame() const {
	(void*)(this);
	ImGui::Render();
}

const WindowParams& Window::GetParams() const {
	return _params;
}

glm::u16vec2 Window::GetSize() const {
	return _params.size;
}

void Window::Hide() const {
	glfwHideWindow(_glfwWindow);
}

void Window::Show() const {
	glfwShowWindow(_glfwWindow);
}