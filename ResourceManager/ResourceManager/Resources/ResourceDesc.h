#pragma once
#include <string>

enum class ResourceType: uint8_t
{
	Disk, //Memory, Net
};

class ResourceDesc
{
public:
	ResourceDesc(const std::string& resourcePath, ResourceType type = ResourceType::Disk);
	ResourceDesc(std::string&& resourcePath, ResourceType type = ResourceType::Disk);

	static uint64_t ComputeHash(const std::string& resourcePath);
	static const ResourceDesc& GetEmptyDesc();

	const std::string& GetPath() const { return _path; }
	uint64_t GetHash() const { return _hash; }
	ResourceType GetType() const { return _type; }

private:
	const std::string _path;
	const uint64_t _hash;
	const ResourceType _type;
};
