#include <iostream>
#include <AppCore/App.h>
#include <AppCore/Window.h>
#include <AppCore/Overlay.h>
#include "ResourceManager/ResourceManager.h"
#include "ResourceManager/Resources/JsonResource.h"
#include "ResourceManager/Resources/TextResource.h"

using namespace ultralight;

int main()
{
	constexpr auto htmlResourcesPath = "htmlResources.json";
	ResourceManager htmlResourceManager;

	if (!htmlResourceManager.InitFrom(htmlResourcesPath))
	{
		std::cout << "Couldn't read " << htmlResourcesPath << std::endl;
		return -1;
	}

    Ref<App> app = App::Create();
    Ref<Window> window = Window::Create(app->main_monitor(), 800, 600, false, kWindowFlags_Titled | kWindowFlags_Resizable);
    window->SetTitle("RanokCAD WebUI");
	app->set_window(window);

	Ref<Overlay> overlay = Overlay::Create(window, window->width(), window->height(), 0, 0);

	TextResource* indexPage = htmlResourceManager.GetResource<TextResource>("IndexPage");
	if (htmlResourceManager.LoadResource(indexPage))
	{
		overlay->view()->LoadHTML(indexPage->GetText().c_str());
	}

    app->Run();

    return 0;
}
