#pragma once

#include "Modules/IModule.h"
#include "OpenglWrap/Application.h"

class SceneObject;
class Material;
class RayMarchWidget;

class RanokCADApp: public Application
{
public:
	RanokCADApp();

	void RenderImGui() override;

private:
	std::shared_ptr<IModule> _activeModule;
};
