#include "DevelopmentModule.h"

#include "ImGui/imgui.h"
#include "OpenglWrap/Core/Material.h"
#include "OpenglWrap/Core/SceneObject.h"
#include "OpenglWrap/Platform/InputManager.h"
#include "RanokCAD/Graphics/RayMarchWidget.h"

DevelopmentModule::DevelopmentModule(InputManager& inputManager) :
	IModule(inputManager),
	_viewport(std::make_shared<RayMarchWidget>(glm::ivec2{800, 600}))
{
	_viewport->Construct();
	inputManager.AddOnMouseMove([&](Window&, const MouseState& state)
	{
		if (state.keys[static_cast<int>(MouseKey::Right)] == KeyState::Pressed)
		{
			_viewport->GetCamera().Rotate({0, state.moved.x, 0});
		}
	});
}

void DevelopmentModule::DrawGui()
{
	ImGui::Begin("DevelopmentViewport");
	_viewport->DrawGui();
	ImGui::End();
}
