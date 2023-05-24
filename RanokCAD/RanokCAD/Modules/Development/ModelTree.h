#pragma once
#include <format>
#include <string>
#include <vector>

#include "RanokCAD/Graphics/ImGuiWidget.h"

enum struct ModelOperations
{
	Union,
	Cross
};

struct ModelTreeInfo: public ImGuiWidget
{
	ModelTreeInfo(std::string name, std::string depthIds);
	ModelTreeInfo(ModelOperations operation, std::string depthIds);

	std::string modelName;
	ModelOperations operation = ModelOperations::Union;
	std::vector<ModelTreeInfo> children;
	std::string depthIds;

	void DrawGui() override;

	template<class... TArgs>
	void AddModel(TArgs&&... args)
	{
		if (isComplex)
			children.emplace_back(std::forward<TArgs>(args)..., std::format("{}.{}", depthIds, children.size()));
	}

	void Transform(ModelOperations replacementOperation);
	void Transform(std::string replacementModelName);


private:
	bool isComplex;
	bool isOpened = false;
};

class ModelTree: public ModelTreeInfo
{
public:
	ModelTree();
};
