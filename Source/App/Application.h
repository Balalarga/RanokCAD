#pragma once

class Window;


class Application
{
public:
	Application(Window& window);

	void RunLoop();
	
	
private:
	Window& _window;
};
