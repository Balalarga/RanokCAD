#pragma once
#include "AssemblyPart.h"


enum class PartsCombineType
{
	Union,
	Subtract
};


class Assembly: public AssemblyPart
{
	static std::map<PartsCombineType, std::string> sCombineTypeViews;
public:
	static void SetPartCombineView(PartsCombineType type, const std::string& view);
	
	using AssemblyPart::AssemblyPart;
	
	explicit Assembly(std::vector<std::unique_ptr<AssemblyPart>>&& parts);

	virtual void AddPart(std::unique_ptr<AssemblyPart>&& part);
	
	void DrawGui() override;
	JsonGeneratorFunctionObject GetJson() override;
	
	bool DrawDetailsPanel() const;

	void SetCombineType(const PartsCombineType& type);

	const std::vector<std::unique_ptr<AssemblyPart>>& Parts() const
	{
		return _parts;
	}


private:
	std::vector<std::unique_ptr<AssemblyPart>> _parts;
	PartsCombineType _combineType = PartsCombineType::Union;
	
	AssemblyPart* _selectedPart = nullptr;
};
