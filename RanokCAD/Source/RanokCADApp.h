#pragma once

#include "Application.h"
#include "Modules/IModule.h"

class RanokCADApp: public Application
{
public:
	RanokCADApp();

	void RenderImGui() override;


private:
	std::shared_ptr<IModule> _activeModule;
};