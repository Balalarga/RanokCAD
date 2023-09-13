#include "AssemblyPart.h"

#include <ImGui/imgui.h>


void AssemblyPart::DetailsView(AssemblyPart& part)
{
	ImGui::BeginChild("Details view");
	glm::vec3 location = part.GetLocation();
	ImGui::DragFloat3("Location", &location.x, 0.05f);
	if (location != part.GetLocation())
		part.SetLocation(location);

	glm::vec4 color = part.GetColor();
	ImGui::ColorEdit4("Color", &color.x);
	if (color != part.GetColor())
		part.SetColor(color);

	ImGui::EndChild();
}


nlohmann::json AssemblyPart::ToJson() const
{
	//@formatter:off
	return {
		{"Name", _name},
		{"Location", {
			{"x", GetLocation().x},
			{"y", GetLocation().y},
			{"z", GetLocation().z},
		}},
		{"Scale", {
			{"x", GetScale().x},
			{"y", GetScale().y},
			{"z", GetScale().z},
		}},
		{"Rotation", {
			{"x", GetRotation().x},
			{"y", GetRotation().y},
			{"z", GetRotation().z},
		}},
		{"Color", {
			{"r", _color.r},
			{"g", _color.g},
			{"b", _color.b},
			{"a", _color.a},
		}},
		{"ExtendBox", {
			{"x", _extendBox.x},
			{"y", _extendBox.y},
			{"z", _extendBox.z},
		}},
	};
	//@formatter:on
}

void AssemblyPart::DrawGui()
{
	if (ImGui::TreeNodeEx(GetName().c_str(), ImGuiTreeNodeFlags_Leaf))
		ImGui::TreePop();
}

AssemblyPart& AssemblyPart::SetName(std::string name)
{
	_name = std::move(name);
	return *this;
}

AssemblyPart& AssemblyPart::SetColor(const glm::vec4& newColor)
{
	_color = newColor;
	return *this;
}

AssemblyPart& AssemblyPart::SetExtendBox(const glm::vec3& extendBox)
{
	_extendBox = extendBox;
	return *this;
}

AssemblyPart& AssemblyPart::SetFunctionCode(const std::string& code)
{
	_functionCode = code;
	return *this;
}
