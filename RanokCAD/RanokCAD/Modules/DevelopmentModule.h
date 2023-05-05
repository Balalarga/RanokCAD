#pragma once
#include <memory>

#include "IModule.h"

class RayMarchWidget;
class SceneObject;
class Material;

class DevelopmentModule: public IModule
{
public:
	DevelopmentModule(InputManager& inputManager);

	void DrawGui() override;


private:
	std::shared_ptr<RayMarchWidget> _viewport;
};
