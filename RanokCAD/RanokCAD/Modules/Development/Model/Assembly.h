#pragma once
#include "AssemblyPart.h"
#include "RanokLang/Generators/MultiObjectShaderGenerator.h"


enum class PartsCombineType
{
	Union,
	Subtract
};

class Assembly: public AssemblyPart
{
public:
	using AssemblyPart::AssemblyPart;
	explicit Assembly(std::vector<std::unique_ptr<AssemblyPart>>&& parts);

	nlohmann::json ToJson() const override;

	virtual void AddPart(std::unique_ptr<AssemblyPart>&& part);
	void DrawGui() override;

	void SetCombineType(const PartsCombineType& type);

	const std::vector<std::unique_ptr<AssemblyPart>>& Parts() const
	{
		return _parts;
	}


private:
	std::vector<std::unique_ptr<AssemblyPart>> _parts;
	PartsCombineType _combineType = PartsCombineType::Union;
};
