#pragma once
#include <memory>

#include "Model/Assembly.h"
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

	void InitInput() const;

	
private:
	std::shared_ptr<RayMarchWidget> _viewport;
	Assembly _assembly;
	bool _bIsViewportFocused = false;
};
