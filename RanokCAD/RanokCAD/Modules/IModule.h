#pragma once
#include "RanokCAD/Graphics/ImGuiWidget.h"


class InputManager;class IModule: public ImGuiWidget
{
public:
	IModule(InputManager& inputManager);


protected:
	InputManager& inputManager;
};
