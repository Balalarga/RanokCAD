#pragma once
#include <string>
#include <glm/vec4.hpp>
#include <nlohmann/json.hpp>

#include "Graphics/ImGuiWidget.h"
#include "OpenglWrap/Core/Transformable.h"
#include "RanokLang/ActionTree.h"
#include "RanokLang/Generators/JsonGenerator.h"


class AssemblyPart: public Transformable, public IImGuiWidget
{
public:
	static bool DetailsView(AssemblyPart& part);

	AssemblyPart() = default;
	AssemblyPart(AssemblyPart&) = delete;
	AssemblyPart(AssemblyPart&&) = default;
	AssemblyPart& operator=(const AssemblyPart&) = delete;
	AssemblyPart& operator=(AssemblyPart&&) = default;
	virtual ~AssemblyPart() = default;

	void DrawGui() override;
	virtual JsonGeneratorFunctionObject GetJson();

	AssemblyPart& SetName(std::string name);
	AssemblyPart& SetColor(const glm::vec4& newColor);
	AssemblyPart& SetExtendBox(const glm::vec3& extendBox);
	AssemblyPart& SetFunctionCode(const std::string& code);
	AssemblyPart& SetFunctionTree(const ActionTree& tree);

	std::string GetName() const
	{
		return _name;
	}

	glm::vec4 GetColor() const
	{
		return _color;
	}

	glm::vec3 GetExtendBox() const
	{
		return _extendBox;
	}

	const ActionTree& GetFunctionTree() const
	{
		return _functionTree;
	}


private:
	std::string _name = "--unnamed--";
	glm::vec4 _color = glm::vec4{0.8f, 0.1f, 0.1f, 1.0f};
	glm::vec3 _extendBox = glm::vec3{0.f};

	ActionTree _functionTree;
};
