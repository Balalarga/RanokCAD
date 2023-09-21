#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include "ModelBase.h"
#include "RanokLang/ActionTree.h"


class Model: public IModelBase
{
public:
	// static bool DetailsView(Model& part)
	// {
	// 	bool bInteracted = false;
	// 	ImGui::BeginGroup();
	// 	glm::vec3 location = part.GetLocation();
	// 	bInteracted |= ImGui::DragFloat3("Location", &location.x, 0.05f);
	// 	if (location != part.GetLocation())
	// 		part.SetLocation(location);
	//
	// 	glm::vec4 color = part.GetColor();
	// 	bInteracted |= ImGui::ColorEdit4("Color", &color.x);
	// 	if (color != part.GetColor())
	// 		part.SetColor(color);
	//
	// 	ImGui::EndGroup();
	// 	return bInteracted;
	// }
	
	Model(std::string name);

	nlohmann::json GenerateJson() const;

	void SetFunctionCode(const std::string& code);
	void SetFunctionTree(const ActionTree& tree);

	virtual ActionTree GetFunctionTree() const
	{
		return _functionTree;
	}

	
private:
	ActionTree _functionTree;
};
