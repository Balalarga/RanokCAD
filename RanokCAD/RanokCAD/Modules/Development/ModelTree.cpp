#include "ModelTree.h"

#include <utility>

#include "ImGui/imgui.h"

ModelTreeInfo::ModelTreeInfo(std::string name, std::string depthIds) :
	modelName(std::move(name)), depthIds(std::move(depthIds)), isComplex(false)
{
}

ModelTreeInfo::ModelTreeInfo(ModelOperations operation, std::string depthIds) :
	operation(operation), depthIds(std::move(depthIds)), isComplex(true)
{
}

void ModelTreeInfo::DrawGui()
{
	ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_SpanFullWidth;
	constexpr ImGuiPopupFlags popupFlags = ImGuiPopupFlags_MouseButtonRight | ImGuiPopupFlags_NoOpenOverItems;

	if (isOpened)
		flags |= ImGuiTreeNodeFlags_DefaultOpen;

	if (!isComplex)
	{
		flags |= ImGuiTreeNodeFlags_Leaf;
		isOpened = ImGui::TreeNodeEx(std::format("{}##{}", modelName, depthIds).c_str(), flags);
		if (isOpened)
		{
			if (ImGui::BeginPopupContextItem("Popup", popupFlags))
			{
				if (ImGui::Selectable("Transform to Aggregation"))
				{
					Transform(ModelOperations::Union);
				}
				ImGui::EndPopup();
			}

			for (ModelTreeInfo& child : children)
				child.DrawGui();

			ImGui::TreePop();
		}
	}
	else
	{
		isOpened = ImGui::TreeNodeEx(
			std::format("{}##{}", operation == ModelOperations::Union ? "OR" : "AND", depthIds).c_str(), flags);
		if (isOpened)
		{
			if (ImGui::BeginPopupContextItem("Popup", popupFlags))
			{
				ImGui::EndPopup();
			}

			for (ModelTreeInfo& child : children)
				child.DrawGui();

			ImGui::TreePop();
		}
	}
}

void ModelTreeInfo::Transform(ModelOperations replacementOperation)
{
	if (!isComplex)
	{
		isComplex = true;
		operation = replacementOperation;
		children.emplace_back(modelName, std::format("{}.{}", depthIds, children.size()));
		isOpened = true;
	}
}

void ModelTreeInfo::Transform(std::string replacementModelName)
{
	if (isComplex)
	{
		isComplex = false;
		modelName = std::move(replacementModelName);
		children.emplace_back(operation, std::format("{}.{}", depthIds, children.size()));
		isOpened = true;
	}
}

ModelTree::ModelTree() : ModelTreeInfo(ModelOperations::Union, "0")
{
}
