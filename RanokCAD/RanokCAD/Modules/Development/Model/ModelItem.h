#pragma once
#include <glm/vec4.hpp>
#include <string>

#include "OpenglWrap/Core/Transformable.h"
#include "RanokLang/ActionTree.h"
#include "RanokLang/Generators/ShaderGenerator.h"
#include "Utils/ClassDefines.h"
#include "Utils/GuiTree.h"

class ModelItem: public Transformable
{
	friend class ModelDetailsView;
public:
	static ShaderGenerator sGenerator;

	DefineGetter(Name, _name);
	DefineGetter(BoundingBox, _bounding);
	DefineGetter(Color, _color);
	DefineGetter(Code, _code);

	DefineConstructSetter(BoundingBox, const std::string&, _name);
	DefineConstructSetter(BoundingBox, const glm::vec3&, _bounding);
	DefineConstructSetter(Color, const glm::vec4&, _color);

	ModelItem& SetCode(const std::string& newCode, bool* bSucceeded = nullptr);

	std::optional<std::string> GetShaderCode() const;


private:
	std::string _name = "<Unnamed>";
	glm::vec3 _bounding{0.f};
	glm::vec4 _color{1.f};

	std::string _code;
	ActionTree _program;
};

class ModelTree: public GuiTree<ModelItem>
{
public:
	static ModelTree sDefaultTree;
	using GuiTree::GuiTree;
	
	bool DrawItem(ImGuiTreeNodeFlags flags) override;
	std::string GetTitle() const override;
};
