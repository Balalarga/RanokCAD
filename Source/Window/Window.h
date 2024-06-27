#pragma once
#include <memory>
#include <string>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"


class Window
{
public:
	struct Params
	{
		std::string title;
		glm::u16vec2 pos;
		glm::u16vec2 size;
		bool fullscreen = false;
		bool vSync = false;
		struct {
			glm::u8vec2 version;	
		} opengl;
	};

	static void SetParams(const Params& params);
	static Window& Get();

	Window();
	~Window();
	
	bool ShouldClose() const;
	
	
protected:
	static void GlfwErrorCallback(int error, const char* description);


private:
	static std::unique_ptr<Window> _gWindow;
	static Params _gParams;

	GLFWwindow* _glfwWindow{};
};
