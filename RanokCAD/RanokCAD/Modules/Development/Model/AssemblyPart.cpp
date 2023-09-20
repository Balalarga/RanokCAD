#include "AssemblyPart.h"

#include <ImGui/imgui.h>
#include "RanokLang/Parser.h"
#include "AssemblyCodeGenerator.h"


bool AssemblyPart::DetailsView(AssemblyPart& part)
{
	bool bInteracted = false;
	ImGui::BeginGroup();
	glm::vec3 location = part.GetLocation();
	bInteracted |= ImGui::DragFloat3("Location", &location.x, 0.05f);
	if (location != part.GetLocation())
		part.SetLocation(location);

	glm::vec4 color = part.GetColor();
	bInteracted |= ImGui::ColorEdit4("Color", &color.x);
	if (color != part.GetColor())
		part.SetColor(color);

	ImGui::EndGroup();
	return bInteracted;
}

void AssemblyPart::DrawGui()
{
	if (ImGui::TreeNodeEx(GetName().c_str(), ImGuiTreeNodeFlags_Leaf))
	{
		_onNodeDraw(this);
		ImGui::TreePop();
	}
}

AssemblyPart* AssemblyPart::IsClicked()
{
	if (ImGui::IsItemClicked())
		return this;
	
	return nullptr;
}

nlohmann::json AssemblyPart::GenerateJson() const
{
	static AssemblyCodeGenerator generator;
	generator.SetAssemblyPart(this);
	generator.Generate(GetFunctionTree());
	
	return {
		{"Name", GetName()},
		{"Function", generator.FlushObject()},
	};
}

void AssemblyPart::SetDrawNode(std::function<void(AssemblyPart*)>&& func)
{
	_onNodeDraw = std::move(func);
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
	static Parser parser;
	_functionTree = parser.Parse(Lexer(code));
	return *this;
}

AssemblyPart& AssemblyPart::SetFunctionTree(const ActionTree& tree)
{
	_functionTree = tree;
	return *this;
}
