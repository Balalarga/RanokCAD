#include <iostream>
#include "App/Application.h"
#include "Window/Window.h"
#include "spdlog/spdlog.h"


int main()
{
	Application app(Window::Get());
	app.RunLoop();


	return 0;
}
