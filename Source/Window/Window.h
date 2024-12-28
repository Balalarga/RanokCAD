#pragma once
#include <memory>
#include <string>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"


struct WindowParams
{
	std::string title = "Ranok3";
	glm::u16vec2 pos = {0, 0};
	glm::u16vec2 size = {1280, 720};
	bool fullscreen = false;
	bool vSync = false;
	struct
	{
		glm::u8vec2 version = {3, 3};
	} opengl;
};


class Window
{
public:
	static void SetParams(const WindowParams& params);
	static Window& Get();

	Window();
	~Window();

	glm::u16vec2 GetSize() const;
	const WindowParams& GetParams() const;

	void Hide();
	void Show();

	void Close();
	bool ShouldClose() const;

	void HandleEvents() const;
	void BeginImGuiFrame() const;
	void EndImGuiFrame() const;
	void SwapBuffers() const;


protected:
	void ImGuiInit();
	void BindGlfwCallbacks();

	void GlfwWindowChangeSizeEvent(int width, int height);

	void GlfwMouseMoveEvent(double xpos, double ypos);
	void GlfwMouseButtonEvent(int button, int action, int mods);

	void GlfwKeyboardButtonEvent(int key, int scancode, int action, int mods);


private:
	static std::unique_ptr<Window> _gWindow;
	static WindowParams _gParams;

	GLFWwindow* _glfwWindow{};
	glm::ivec2 _size;
};