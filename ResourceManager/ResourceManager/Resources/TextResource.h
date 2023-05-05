#pragma once
#include "Resource.h"

class TextResource: public Resource
{
public:
	using Resource::Resource;

    Resource* GetPrototype(const ResourceDesc& desc) override;
	std::string GetResourceType() override;

	const std::string& GetText() const { return _data; }

protected:
	bool LoadImpl(std::istream& stream) override;
	void SaveImpl(std::ostream& stream) override;
	void UnloadImpl() override;


private:
	std::string _data;
};