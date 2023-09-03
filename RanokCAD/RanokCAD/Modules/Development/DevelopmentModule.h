#pragma once
#include <memory>

#include "Model/ModelItem.h"
#include "Modules/IModule.h"

struct ImVec2;
class RayMarchWidget;
class SceneObject;
class Material;

class DevelopmentModule: public IModule
{
public:
	DevelopmentModule(glm::ivec2 windowSize, InputManager& inInputManager);

	void DrawGui() override;


protected:
	void DrawViewport();
	void DrawTreeView();
	void DrawToolBar();
	void DrawMenuBar();


private:
	std::shared_ptr<RayMarchWidget> _viewport;
	ModelTree _modelTree;
	bool _bIsViewportFocused = false;
};
