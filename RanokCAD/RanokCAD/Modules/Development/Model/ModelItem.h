#pragma once
#include <glm/vec4.hpp>
#include <string>

#include "OpenglWrap/Core/Transformable.h"
#include "Utils/GuiTree.h"
#include "RanokLang/ActionTree.h"
#include "RanokLang/Generators/ShaderGenerator.h"

class ModelItem: public Transformable
{
public:
	static ShaderGenerator sGenerator;

	ModelItem(const std::string& newCode, glm::vec3 newBounding);

	const std::string& GetCode() const
	{
		return _code;
	}

	const glm::vec3& GetBoundingBox() const
	{
		return _bounding;
	}

	bool UpdateCode(const std::string& newCode, glm::vec3 newBounding);

	std::optional<std::string> GetShaderCode() const;


private:
	std::string _code;
	ActionTree _program;
	glm::vec3 _bounding{1.f};
};

class ModelTree: public GuiTree<ModelItem>
{
public:
	void DrawItem() override;
	std::string GetTitle() const override;
};
