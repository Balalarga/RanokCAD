#pragma once
#include <string>
#include <glm/vec3.hpp>
#include "OpenglWrap/Core/Transformable.h"


class IModelBase: public Transformable
{
public:
	IModelBase(std::string name)
		: _name(std::move(name))
	{
	}

	void SetName(std::string name)
	{
		_name = name;
	}

	void SetColor(const glm::vec4& color)
	{
		_color = color;
	}

	void SetExtendBox(const glm::vec3& extendBox)
	{
		_extendBox = extendBox;
	}

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


private:
	std::string _name;
	glm::vec4 _color = glm::vec4{0.7f, 0.1f, 0.2f, 1.0f};
	glm::vec3 _extendBox = glm::vec3{0.f};
};
