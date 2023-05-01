#include "DevelopmentModule.h"

#include "ImGui/imgui.h"
#include "OpenglWrap/Core/Material.h"
#include "OpenglWrap/Core/SceneObject.h"
#include "RanokCAD/Graphics/RayMarchWidget.h"

DevelopmentModule::DevelopmentModule() : _viewport(std::make_shared<RayMarchWidget>(glm::ivec2{800, 600}))
{
	_viewport->Construct();
}

void DevelopmentModule::DrawGui()
{
	ImGui::Begin("DevelopmentViewport");
	_viewport->DrawGui();
	ImGui::End();
}
