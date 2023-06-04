#pragma once
#include <memory>

#include "../IModule.h"
#include "Model\GuiTree.h"

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
	void DrawRightPanel();
	void DrawTreeView();
	void DrawLeftPanel(const ImVec2& size);


private:
	std::shared_ptr<RayMarchWidget> _viewport;
	ModelTree _modelTree;
};
