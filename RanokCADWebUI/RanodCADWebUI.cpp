#include <iostream>
#include <AppCore/App.h>
#include <AppCore/Window.h>
#include <AppCore/Overlay.h>

#include "RanokWebUIApp.h"
#include "ResourceManager/ResourceManager.h"
#include "ResourceManager/Resources/JsonResource.h"
#include "ResourceManager/Resources/TextResource.h"

using namespace ultralight;

int main()
{
	RanokWebUIApp app(800, 600);

    app.Run();

    return 0;
}
