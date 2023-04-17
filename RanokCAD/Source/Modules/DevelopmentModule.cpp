#include "DevelopmentModule.h"

#include "Graphics/RayMarchWidget.h"
#include "imgui.h"

DevelopmentModule::DevelopmentModule() : _viewport(std::make_shared<RayMarchWidget>(glm::ivec2{800, 600}, 3))
{
	_viewport->Init();
}

void DevelopmentModule::DrawGui()
{
	ImGui::Begin("DevelopmentViewport");
	_viewport->DrawGui();
	ImGui::End();
}