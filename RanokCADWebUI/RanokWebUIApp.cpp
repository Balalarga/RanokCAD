#include "RanokWebUIApp.h"


#include "ResourceManager/Resources/TextResource.h"


constexpr auto htmlResourcesPath = "htmlResources.json";


RanokWebUIApp::RanokWebUIApp(unsigned width, unsigned height)
{
	_app = App::Create();
	_window = Window::Create(_app->main_monitor(), width, height, false, kWindowFlags_Titled | kWindowFlags_Resizable);
	_app->set_window(*_window.get());
	_overlay = Overlay::Create(*_window.get(), 0.2, 0.2, 0.2, 0);

	_window->SetTitle("RanokCAD WebUI");

	_window->set_listener(this);
	_overlay->view()->set_view_listener(this);

	RanokWebUIApp::OnResize(_window->width(), _window->height());

	if (_htmlResourceManager.InitFrom(htmlResourcesPath))
	{
		TextResource* indexPage = _htmlResourceManager.GetResource<TextResource>("IndexPage");
		if (_htmlResourceManager.LoadResource(indexPage))
			_overlay->view()->LoadHTML(indexPage->GetText().c_str());
	}
}

void RanokWebUIApp::OnClose()
{
}

void RanokWebUIApp::OnResize(uint32_t width, uint32_t height)
{
	_overlay->Resize(width, height);
}