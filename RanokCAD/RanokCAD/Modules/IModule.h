#pragma once
#include "Graphics/ImGuiWidget.h"

class InputManager;class IModule: public ImGuiWidget
{
public:
	IModule(InputManager& inputManager);


protected:
	InputManager& inputManager;
};
