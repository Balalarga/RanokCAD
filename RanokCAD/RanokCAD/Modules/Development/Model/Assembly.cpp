#include "Assembly.h"

#include "Utils/GuiTree.h"


Assembly::Assembly(std::vector<std::unique_ptr<AssemblyPart>>&& parts)
	: _parts(std::move(parts))
{
}

nlohmann::json Assembly::ToJson() const
{
	nlohmann::json json = AssemblyPart::ToJson();

	json["CombineType"] = _combineType == PartsCombineType::Subtract ? "Subtract" : "Union";
	nlohmann::json& subObjects = json["SubObjects"];
	for (const std::unique_ptr<AssemblyPart>& part : _parts)
		subObjects.emplace_back(part->ToJson());
	json["SubObjects"] = subObjects;

	return json;
}

void Assembly::AddPart(std::unique_ptr<AssemblyPart>&& part)
{
	_parts.emplace_back(std::move(part));
}

void Assembly::DrawGui()
{
	static ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None;
	static bool bOpened = false;

	if (bOpened)
		flags |= ImGuiTreeNodeFlags_DefaultOpen;
	if (_parts.empty())
		flags |= ImGuiTreeNodeFlags_Leaf;

	bOpened = ImGui::TreeNodeEx(GetName().c_str(), flags);
	if (bOpened)
	{
		for (const std::unique_ptr<AssemblyPart>& part : _parts)
			part->DrawGui();

		ImGui::TreePop();
	}
}

void Assembly::SetCombineType(const PartsCombineType& type)
{
	_combineType = type;
}
