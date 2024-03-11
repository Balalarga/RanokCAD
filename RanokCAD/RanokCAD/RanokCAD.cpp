#include <iostream>

#include "RanokCADApp.h"


int main(int argc, char** argv)
{
	RanokCADApp::Params params;
	params.width = 1280;
	params.height = 720;
	const auto App = RanokCADApp::Init(params);
	if (!App)
		return 1;

	App->Run();

	return 0;
}
