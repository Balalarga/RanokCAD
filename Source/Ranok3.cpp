#include <iostream>
#include <map>
#include "App/Application.h"
#include "Window/Window.h"
#include "spdlog/spdlog.h"


int main()
{
	//	Window::SetParams(Window::Params{});

	//	Application app;
	//	app.RunLoop();


	std::map<int, std::string> map;
	map[0] = "asd";
	map[1] = "asd";
	map[10] = "asd";
	map[5] = "asd";
	for (auto& [k, v]: map)
	{
		std::cout << k << std::endl;
		std::cout << v << std::endl;
		std::cout << "---------------" << std::endl;
	}

	return 0;
}
