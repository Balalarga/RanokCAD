#include "Assembly.h"

#include "RanokLang/Parser.h"
#include "Utils/GuiTree.h"


std::map<PartsCombineType, std::string> Assembly::sCombineTypeViews{
	{PartsCombineType::Subtract, "& {}"}, {PartsCombineType::Union, "| {}"},
};


void Assembly::SetPartCombineView(PartsCombineType type, const std::string& view)
{
	sCombineTypeViews[type] = view;
}

Assembly::Assembly(std::vector<std::unique_ptr<AssemblyPart>>&& parts)
	: _parts(std::move(parts))
{
	UpdateCode();
}

void Assembly::AddPart(std::unique_ptr<AssemblyPart>&& part)
{
	part->SetDrawNode(
		[this](AssemblyPart* subPart)
		{
			if (auto clickedItem = subPart->IsClicked())
			{
				_selectedPart = clickedItem;
				_onNodeDraw(_selectedPart);
			}
		});
	_parts.emplace_back(std::move(part));
	UpdateCode();
}

nlohmann::json Assembly::GenerateJson() const
{
	nlohmann::json json;
	for (auto& part : _parts)
	{
		auto partJson = part->GenerateJson();
		if (partJson.is_array())
		{
			for (auto& subPart : partJson)
				json.push_back(subPart);
		}
		else
		{
			json.push_back(partJson);
		}
	}

	json.push_back(AssemblyPart::GenerateJson());
	return json;
}

void Assembly::DrawGui()
{
	static ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;

	if (_bOpened)
		flags |= ImGuiTreeNodeFlags_DefaultOpen;
	if (_parts.empty())
		flags |= ImGuiTreeNodeFlags_Leaf;

	const std::string nodeTitle = std::vformat(sCombineTypeViews[_combineType], std::make_format_args(GetName()));
	if (_bOpened = ImGui::TreeNodeEx(nodeTitle.c_str(), flags); _bOpened)
	{
		_onNodeDraw(this);
		for (const std::unique_ptr<AssemblyPart>& part : _parts)
			part->DrawGui();

		ImGui::TreePop();
	}
}

AssemblyPart* Assembly::IsClicked()
{
	if (const auto clickedItem = AssemblyPart::IsClicked())
		return clickedItem;

	for (auto& part : _parts)
	{
		if (part->IsClicked())
			return part.get();
	}

	return nullptr;
}

bool Assembly::DrawDetailsPanel() const
{
	if (_selectedPart)
		return DetailsView(*_selectedPart);

	return false;
}

void Assembly::SetCombineType(const PartsCombineType& type)
{
	_combineType = type;
}

void Assembly::UpdateCode()
{
	std::ostringstream codeStream;

	for (auto& part : _parts)
		codeStream << "def " << part->GetName() << "(s[3]){ return 0; };\n";

	codeStream << "\ndef main(s[3]){\n";
	codeStream << "return ";
	if (_parts.empty())
		codeStream << "0";
	
	for (size_t i = 0; i < _parts.size(); ++i)
	{
		codeStream << _parts[i]->GetName() << "(s)";
		if ((i == 0 && _parts.size() < 2) || i != _parts.size() - 1)
			codeStream << (_combineType == PartsCombineType::Subtract ? "&" : "|");
	}
	codeStream << ";\n}";

	SetFunctionCode(codeStream.str());
}
