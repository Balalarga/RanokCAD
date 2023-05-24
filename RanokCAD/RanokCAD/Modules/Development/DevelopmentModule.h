#pragma once
#include <memory>

#include "../IModule.h"
#include "ModelTree.h"

struct ImVec2;
class RayMarchWidget;
class SceneObject;
class Material;

class DevelopmentModule: public IModule
{
public:
	DevelopmentModule(InputManager& inInputManager);

	void DrawGui() override;


protected:
	void DrawViewport();
	void DrawTreeView();
	void DrawModelPicker(const ImVec2& size);


private:
	std::shared_ptr<RayMarchWidget> _viewport;
	ModelTree _modelTree;
};
