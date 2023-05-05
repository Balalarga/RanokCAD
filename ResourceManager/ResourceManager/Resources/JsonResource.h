#pragma once

#include "Resource.h"
#include <nlohmann/json.hpp>


class JsonResource: public Resource
{
public:
	using Resource::Resource;

	std::string GetResourceType() override;
	const nlohmann::json& GetJson() const { return _json; }
	nlohmann::json& GetJson() { return _json; }

    Resource* GetPrototype(const ResourceDesc& desc) override;

protected:
	bool LoadImpl(std::istream& stream) override;
	void SaveImpl(std::ostream& stream) override;
	void UnloadImpl() override;

	nlohmann::json _json;
};

class JsonResourceWritable: public JsonResource
{
public:
	JsonResourceWritable(const ResourceDesc& desc);

	const nlohmann::json& GetMutableJson() { return _json; }
};