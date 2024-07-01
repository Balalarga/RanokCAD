#pragma once

class Window;


struct AppParams
{
	unsigned fps = 60;
};


class Application
{
public:
	explicit Application(Window& window, const AppParams& params = {});

	void RunLoop();


protected:
	void NormalizeParams();
	void Render();
	void RenderImGui();
	void Update(double dt);


private:
	AppParams _params;
	Window& _window;
};
