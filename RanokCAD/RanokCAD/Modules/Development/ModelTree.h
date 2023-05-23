#pragma once
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
	ModelTreeInfo(std::string name);
	ModelTreeInfo(ModelOperations operation);

	std::string modelName;
	ModelOperations operation = ModelOperations::Union;
	std::vector<ModelTreeInfo> children;

	void DrawGui() override;
	void AddModel(const ModelTreeInfo& info);

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
