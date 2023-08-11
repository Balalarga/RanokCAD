#pragma once

#include "Modules/IModule.h"
#include "OpenglWrap/Application.h"


class RanokCADApp: public Application
{
public:
	RanokCADApp();

	void SetDefaultStyle();

	void RenderImGui() override;


private:
	std::shared_ptr<IModule> _activeModule;
};
