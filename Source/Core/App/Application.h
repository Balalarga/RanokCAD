#pragma once
#include "Window/Window.h"


struct AppParams {
	unsigned fps = 60;
	WindowParams windowParams;
};


class Application {
public:
	explicit Application(AppParams params = {});

	void Launch();


protected:
	void Render();
	void RenderImGui();
	void Update(double dt);


private:
	void MainLoop();


private:
	AppParams _params;
	Window _window;
};
