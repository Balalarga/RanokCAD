#pragma once
#include "Model.h"


struct AssemblyPart
{
	enum class CombineType: uint8_t
	{
		Union,
		Subtract
	};
	
	AssemblyPart(Model model, CombineType combineType)
		: model(std::move(model))
		, combineType(combineType)
	{
	}

	Model model;
	CombineType combineType;
};


class Assembly: public IModelBase
{
public:
	explicit Assembly(std::string name);
	explicit Assembly(std::string name, std::vector<AssemblyPart> parts);

	void AddPart(AssemblyPart&& part);
	nlohmann::json GenerateJson() const;

	const std::vector<AssemblyPart>& GetParts() const
	{
		return _parts;
	}


private:
	std::vector<AssemblyPart> _parts;
};
