#pragma once
#include <glm/vec2.hpp>
#include "Graphics/ImGuiWidget.h"

class InputManager;


class IModule: public ImGuiWidget
{
public:
	IModule(glm::ivec2 windowSize, InputManager& inputManager);

	const glm::ivec2& GetWindowSize() const
	{
		return _windowSize;
	}


protected:
	InputManager& inputManager;
	glm::ivec2 _windowSize;
};
