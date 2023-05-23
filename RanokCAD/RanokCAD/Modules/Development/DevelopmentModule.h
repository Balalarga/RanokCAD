#pragma once
#include <memory>

#include "../IModule.h"
#include "ModelTree.h"

class RayMarchWidget;
class SceneObject;
class Material;

class DevelopmentModule: public IModule
{
public:
	DevelopmentModule(InputManager& inInputManager);

	void DrawGui() override;


private:
	std::shared_ptr<RayMarchWidget> _viewport;
	ModelTree _modelTree;
};
