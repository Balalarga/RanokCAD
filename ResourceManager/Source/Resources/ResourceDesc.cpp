#include "ResourceDesc.h"

ResourceDesc::ResourceDesc(const std::string& resourcePath, ResourceType type):
	_path(resourcePath),
	_hash(ComputeHash(_path)),
	_type(type)
{
}

ResourceDesc::ResourceDesc(std::string&& resourcePath, ResourceType type):
	_path(std::move(resourcePath)),
	_hash(ComputeHash(_path)),
	_type(type)
{
}

const ResourceDesc& ResourceDesc::GetEmptyDesc()
{
	static ResourceDesc emptyDesc("");
	return emptyDesc;
}

uint64_t ResourceDesc::ComputeHash(const std::string &resourcePath)
{
	static std::hash<std::string> hasher;
	return hasher(resourcePath);
}
