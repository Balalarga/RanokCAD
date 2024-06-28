#include "Application.h"
#include "../Window/Window.h"


Application::Application(Window& window) : _window(window)
{
}

void Application::RunLoop()
{
	while (!_window.ShouldClose())
	{
		_window.HandleEvents();


		_window.SwapBuffers();
	}
}
