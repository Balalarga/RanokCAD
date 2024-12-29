#pragma once
#include <memory>
#include <string>
#include <nlohmann/json.hpp>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"


struct WindowParams {
	std::string title = "Ranok3";
	glm::u16vec2 pos = { 0, 0 };
	glm::u16vec2 size = { 1280, 720 };
	bool fullscreen = false;
	bool vSync = false;

	struct {
		glm::u8vec2 version = { 3, 3 };
	} opengl;
};

void to_json(nlohmann::json& j, const WindowParams& p);
void from_json(const nlohmann::json& j, WindowParams& p);


class Window {
public:
	explicit Window(WindowParams params = {});
	~Window();

	glm::u16vec2 GetSize() const;

	void SetParams(const WindowParams& params);
	const WindowParams& GetParams() const;

	void Hide() const;
	void Show() const;

	void Close() const;
	bool ShouldClose() const;

	void HandleEvents() const;
	void BeginImGuiFrame() const;
	void EndImGuiFrame() const;
	void SwapBuffers() const;


protected:
	static Window* GetWindow(GLFWwindow* glfwWindow);

	void ImGuiInit();
	void GlfwInit();
	void BindGlfwCallbacks() const;

	void GlfwWindowChangeSizeEvent(int width, int height);

	void GlfwMouseMoveEvent(double xpos, double ypos);
	void GlfwMouseButtonEvent(int button, int action, int mods);

	void GlfwKeyboardButtonEvent(int key, int scancode, int action, int mods);


private:
	WindowParams _params;
	GLFWwindow* _glfwWindow{};
};