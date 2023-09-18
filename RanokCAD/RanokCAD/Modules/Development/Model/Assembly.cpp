#include "Assembly.h"
#include "Utils/GuiTree.h"


std::map<PartsCombineType, std::string> Assembly::sCombineTypeViews
{
	{PartsCombineType::Subtract, "&"},
	{PartsCombineType::Union, "|"},
};


void Assembly::SetPartCombineView(PartsCombineType type, const std::string& view)
{
	sCombineTypeViews[type] = view;
}

Assembly::Assembly(std::vector<std::unique_ptr<AssemblyPart>>&& parts)
	: _parts(std::move(parts))
{
}

void Assembly::AddPart(std::unique_ptr<AssemblyPart>&& part)
{
	_parts.emplace_back(std::move(part));
}

void Assembly::DrawGui()
{
	static ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
	static bool bOpened = false;

	if (bOpened)
		flags |= ImGuiTreeNodeFlags_DefaultOpen;
	if (_parts.empty())
		flags |= ImGuiTreeNodeFlags_Leaf;

	static std::string nodeTitle = std::vformat(sCombineTypeViews[_combineType], std::make_format_args(GetName()));
	if (bOpened = ImGui::TreeNodeEx(nodeTitle.c_str(), flags); bOpened)
	{
		for (const std::unique_ptr<AssemblyPart>& part : _parts)
		{
			if (ImGui::TreeNodeEx(part->GetName().c_str(), ImGuiTreeNodeFlags_Leaf))
			{
				if (ImGui::IsItemClicked())
					_selectedPart = part.get();
						
				ImGui::TreePop();
			}
		}

		ImGui::TreePop();
	}
}

JsonGeneratorFunctionObject Assembly::GetJson()
{
	JsonGeneratorFunctionObject selfCode = AssemblyPart::GetJson();
	for (const std::unique_ptr<AssemblyPart>& part : _parts)
		selfCode.functions.emplace_back(part->GetJson());
	
	return selfCode;
}

bool Assembly::DrawDetailsPanel() const
{
	if (!_selectedPart)
		return false;
	
	return DetailsView(*_selectedPart);
}

void Assembly::SetCombineType(const PartsCombineType& type)
{
	_combineType = type;
}
