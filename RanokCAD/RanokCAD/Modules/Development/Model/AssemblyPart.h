#pragma once
#include <string>
#include <glm/vec4.hpp>
#include <nlohmann/json.hpp>

#include "Graphics/ImGuiWidget.h"
#include "OpenglWrap/Core/Transformable.h"


class AssemblyPart: public Transformable, public ImGuiWidget
{
public:
	static void DetailsView(AssemblyPart& part);

	AssemblyPart() = default;
	AssemblyPart(AssemblyPart&) = delete;
	AssemblyPart(AssemblyPart&&) = default;
	AssemblyPart& operator=(const AssemblyPart&) = delete;
	AssemblyPart& operator=(AssemblyPart&&) = default;
	virtual ~AssemblyPart() = default;

	virtual nlohmann::json ToJson() const;
	void DrawGui() override;

	AssemblyPart& SetName(std::string name);
	AssemblyPart& SetColor(const glm::vec4& newColor);
	AssemblyPart& SetExtendBox(const glm::vec3& extendBox);
	AssemblyPart& SetFunctionCode(const std::string& code);

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

	const std::string& GetFunctionCode() const
	{
		return _functionCode;
	}


private:
	std::string _name = "--unnamed--";
	glm::vec4 _color = glm::vec4{0.8f, 0.1f, 0.1f, 1.0f};
	glm::vec3 _extendBox = glm::vec3{0.f};

	std::string _functionCode;
};
