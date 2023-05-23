#include "ModelTree.h"

#include <format>
#include <utility>

#include "ImGui/imgui.h"

ModelTreeInfo::ModelTreeInfo(std::string name) : modelName(std::move(name)), isComplex(false)
{
}

ModelTreeInfo::ModelTreeInfo(ModelOperations operation) : operation(operation), isComplex(true)
{
}

void ModelTreeInfo::DrawGui()
{
	ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None;

	if (isOpened)

		flags |= ImGuiTreeNodeFlags_DefaultOpen;

	if (!isComplex)
	{
		flags |= ImGuiTreeNodeFlags_Leaf;
		isOpened = ImGui::TreeNodeEx(std::format("{}", modelName).c_str(), flags);
		if (isOpened)
		{
			if (ImGui::BeginPopupContextItem("Popup",
											 ImGuiPopupFlags_MouseButtonRight | ImGuiPopupFlags_NoOpenOverItems))
			{
				if (ImGui::Selectable("Transform to Aggregation"))
				{
					Transform(ModelOperations::Union);
				}
				ImGui::EndPopup();
			}

			for (ModelTreeInfo& child : children)
			{
				child.DrawGui();
			}
			ImGui::TreePop();
		}
	}
	else
	{
		isOpened = ImGui::TreeNodeEx(operation == ModelOperations::Union ? "Union" : "Cross", flags);
		if (isOpened)
		{
			if (ImGui::BeginPopupContextItem("Popup",
											 ImGuiPopupFlags_MouseButtonRight | ImGuiPopupFlags_NoOpenOverItems))
			{
				if (ImGui::Selectable("Add model"))
				{
				}
				ImGui::EndPopup();
			}

			for (ModelTreeInfo& child : children)
			{
				child.DrawGui();
			}
			ImGui::TreePop();
		}
	}
}

void ModelTreeInfo::AddModel(const ModelTreeInfo& info)
{
	if (isComplex)
		children.push_back(info);
}

void ModelTreeInfo::Transform(ModelOperations replacementOperation)
{
	if (!isComplex)
	{
		isComplex = true;
		operation = replacementOperation;
		children.emplace_back(modelName);
		isOpened = true;
	}
}

void ModelTreeInfo::Transform(std::string replacementModelName)
{
	if (isComplex)
	{
		isComplex = false;
		modelName = std::move(replacementModelName);
		children.emplace_back(operation);
		isOpened = true;
	}
}

ModelTree::ModelTree() : ModelTreeInfo(ModelOperations::Union)
{
}
