#include "ModelDetailsView.h"


void ModelDetailsView::SetModel(ModelItem* item)
{
}

void ModelDetailsView::DrawGui()
{
	if (!_model)
		return;
	
	ImGui::BeginChild("Details view");
	glm::vec3 location = _model->GetLocation();
	ImGui::DragFloat3("Position", &location.x, 0.05);
	if (location != _model->GetLocation())
		_model->SetLocation(location);
	
	glm::vec4 color = _model->GetColor();
	ImGui::ColorEdit4("Color", &color.x, 0.05);
	if (color != _model->GetColor())
		_model->SetColor(color);
	
	ImGui::EndChild();
}
