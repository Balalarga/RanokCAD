#include "IModule.h"


IModule::IModule(glm::ivec2 windowSize, InputManager& inputManager)
	: inputManager(inputManager)
	, _windowSize(windowSize)
{
}
