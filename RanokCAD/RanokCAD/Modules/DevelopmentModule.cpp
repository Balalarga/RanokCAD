#include "DevelopmentModule.h"

#include "ImGui/imgui.h"
#include "OpenglWrap/Core/Material.h"
#include "OpenglWrap/Core/SceneObject.h"
#include "OpenglWrap/Platform/InputManager.h"
#include "RanokCAD/Graphics/RayMarchWidget.h"

DevelopmentModule::DevelopmentModule(InputManager& inputManager) :
	IModule(inputManager), _viewport(std::make_shared<RayMarchWidget>(glm::ivec2{800, 600}))
{
	_viewport->Construct();
	inputManager.AddOnMouseMove(
		[&](Window&, const MouseState& state)
		{
			if (state.keys[static_cast<int>(MouseKey::Right)] == KeyState::Pressed)
			{
				_viewport->GetCamera().Rotate({-state.moved.y / 10.f, state.moved.x / 10.f, 0});
			}
		});

	inputManager.Add(SDL_SCANCODE_W,
					 [&](Window&, const KeyState& state)
					 {
						 if (state == KeyState::Pressed || state == KeyState::Repeated)
						 {
							 _viewport->GetCamera().Move({0, 0, 0.1});
						 }
					 });

	inputManager.Add(SDL_SCANCODE_S,
					 [&](Window&, const KeyState& state)
					 {
						 if (state == KeyState::Pressed || state == KeyState::Repeated)
						 {
							 _viewport->GetCamera().Move({0, 0, -0.1});
						 }
					 });

	inputManager.Add(SDL_SCANCODE_D,
					 [&](Window&, const KeyState& state)
					 {
						 if (state == KeyState::Pressed || state == KeyState::Repeated)
						 {
							 _viewport->GetCamera().Move({0, 0.1, 0});
						 }
					 });

	inputManager.Add(SDL_SCANCODE_A,
					 [&](Window&, const KeyState& state)
					 {
						 if (state == KeyState::Pressed || state == KeyState::Repeated)
						 {
							 _viewport->GetCamera().Move({0, -0.1, 0});
						 }
					 });
}

void DevelopmentModule::DrawGui()
{
	ImGui::Begin("DevelopmentViewport");
	_viewport->DrawGui();
	ImGui::End();
}
