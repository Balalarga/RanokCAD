#pragma once


class RanokCADApp
{
public:
	struct Params
	{
		int width;
		int height;
	};

	static RanokCADApp* Init(const Params& params);
	static RanokCADApp* Get();

	~RanokCADApp();

	void Run();


protected:
	RanokCADApp() = default;
	explicit RanokCADApp(const Params& params);

	void HandleKeyboard();
	void Graphics();


private:
	Params _params;
	class GLFWwindow* _window;


	static void GlfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void KeyCallback(int key, int scancode, int action, int mods);
	static void GlfwCursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
	void CursorPositionCallback(double xpos, double ypos);
	static void GlfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	void MouseButtonCallback(int button, int action, int mods);
};
