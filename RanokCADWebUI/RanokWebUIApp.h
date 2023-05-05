#pragma once
#include <AppCore/App.h>
#include <AppCore/Overlay.h>
#include <AppCore/Window.h>

#include "ResourceManager/ResourceManager.h"

using namespace ultralight;

class RanokWebUIApp:
	public WindowListener,
	public ViewListener
{
public:
	RanokWebUIApp(unsigned width, unsigned height);

	void OnClose() override;
	void OnResize(uint32_t width, uint32_t height) override;

	void Run() const
	{
		_app->Run();
	}


private:
	RefPtr<App> _app;
	RefPtr<Window> _window;
	RefPtr<Overlay> _overlay;

	ResourceManager _htmlResourceManager;
};
