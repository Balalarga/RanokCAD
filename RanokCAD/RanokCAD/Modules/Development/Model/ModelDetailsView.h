#pragma once
#include "Graphics/ImGuiWidget.h"
#include "ModelItem.h"


class ModelDetailsView: public ImGuiWidget
{
public:
	void SetModel(ModelItem* item);
	void DrawGui() override;
	

private:
	ModelItem* _model = nullptr;
};
