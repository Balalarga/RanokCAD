#include <iostream>

#include "RanokCADApp.h"
#include "RanokResources.h"
#include "RanokLang/Generators/MultiObjectShaderGenerator.h"


int main(int argc, char** argv)
{
	std::cout << std::filesystem::current_path() << std::endl;
	constexpr auto resourceRegistry = "resourceRegistry.json";
	if (!RanokResources::Get().InitFrom(resourceRegistry))
	{
		std::cout << "Couldn't read " << resourceRegistry << std::endl;
		return -1;
	}

	RanokCADApp mainWindow;

	mainWindow.Run();

	return 0;
}
