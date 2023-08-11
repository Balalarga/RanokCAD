#include "JsonResource.h"

JsonResource::JsonResource(const ResourceDesc& desc)
	: Resource(desc)
{
}

std::string JsonResource::GetResourceType()
{
	return "Json";
}

Resource* JsonResource::GetPrototype(const ResourceDesc& desc)
{
	return new JsonResource(desc);
}

bool JsonResource::LoadImpl(std::istream& stream)
{
	int s[] = { 1, 2, 3 };

	stream >> _json;
	return stream.good();
}

void JsonResource::SaveImpl(std::ostream& stream)
{
	stream << _json;
}

void JsonResource::UnloadImpl()
{
	_json.clear();
}

JsonResourceWritable::JsonResourceWritable(const ResourceDesc& desc)
	: JsonResource(desc)
{
}
