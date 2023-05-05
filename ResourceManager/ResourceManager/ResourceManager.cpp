#include "ResourceManager.h"

#include <fstream>

#include "FileUtils.h"
#include "Resources/JsonResource.h"
#include "Resources/Resource.h"
#include "Resources/TextResource.h"
#include "nlohmann/json.hpp"

const std::string ResourceManager::sResourceRegistryName = "__ResourceRegistry";

ResourceManager::ResourceManager()
{
	ResourceManager::AddDefaultSupportedResources();
}

ResourceManager::~ResourceManager()
{
	for (const std::shared_ptr<Resource>& res : _resourcesArray)
	{
		res->Unload();
	}
}

void ResourceManager::AddDefaultSupportedResources()
{
	AddSupportedResourceType<JsonResource>();
	AddSupportedResourceType<TextResource>();
}

bool ResourceManager::InitFrom(const std::string& configPath)
{
	if (!FileUtils::IsFileExists(configPath))
	{
		return false;
	}

	auto* configRes = AddResource<JsonResource>(sResourceRegistryName, {configPath});
	if (LoadResource(configRes))
	{

		from_json(configRes->GetJson(), *this);
		_configPath = {configPath};
		return true;
	}

	return false;
}

bool ResourceManager::Save(const std::string& configPath) const
{
	if (configPath.empty())
	{
		if (auto* resRegistry = GetResource<JsonResource>(sResourceRegistryName))
		{
			to_json(resRegistry->GetJson(), *this);
			SaveResource(resRegistry);
			return true;
		}
	}
	else if (const std::shared_ptr<std::ofstream> writer = FileUtils::CreateFileWriter(configPath))
	{
		nlohmann::json json;
		to_json(json, *this);
		*writer << json;
		return true;
	}

	return false;
}

Resource* ResourceManager::FindSupportedType(const std::string& name)
{
	const auto it = _supportedTypes.find(name);
	if (it == _supportedTypes.end())
	{
		return nullptr;
	}

	return it->second.get();
}

Resource* ResourceManager::AddResource(const std::string& tag, Resource* proto, const ResourceDesc& desc)
{
	_resourcesArray.push_back(_resources.emplace(tag, proto->GetPrototype(desc)).first->second);
	return _resourcesArray.back().get();
}

Resource* ResourceManager::GetResource(const std::string& tag) const
{
	const auto it = _resources.find(tag);
	if (it == _resources.end())
	{
		return nullptr;
	}

	return it->second.get();
}

Resource* ResourceManager::GetOrAddResource(const std::string& tag, Resource* proto, const ResourceDesc& desc)
{
	if (Resource* res = GetResource(tag))
	{
		return res;
	}

	_resourcesArray.push_back(_resources.emplace(tag, proto->GetPrototype(desc)).first->second);
	return _resourcesArray.back().get();
}

int ResourceManager::LoadAll(std::vector<std::shared_ptr<Resource>>* failed) const
{
	int failCount = 0;

	for (const std::shared_ptr<Resource>& res : _resourcesArray)
	{
		if (!LoadResource(res.get()))
		{
			++failCount;
			if (failed)
				failed->push_back(res);
		}
	}

	return failCount;
}

bool ResourceManager::LoadResource(Resource* resource) const
{
	if (!resource)
		return false;

	if (const std::shared_ptr<std::ifstream> reader = FileUtils::CreateFileReader(GetResourcePath(resource)))
		return resource->Load(*reader);

	return false;
}

bool ResourceManager::LoadResource(const std::string& tag) const
{
	if (Resource* resource = GetResource(tag))
	{
		return LoadResource(resource);
	}

	return false;
}

bool ResourceManager::SaveResource(Resource* resource) const
{
	if (!resource)
	{
		return false;
	}

	if (const std::shared_ptr<std::ofstream> writer = FileUtils::CreateFileWriter(GetResourcePath(resource)))
	{
		resource->Save(*writer);
		return true;
	}

	return false;
}

bool ResourceManager::SaveResource(const std::string& tag) const
{
	return SaveResource(GetResource(tag));
}

std::string ResourceManager::GetResourcePath(const std::string& tag) const
{
	return GetResourcePath(GetResource(tag));
}

std::string ResourceManager::GetResourcePath(const Resource* res) const
{
	if (res)
	{
		return (_baseDir / res->GetDesc().GetPath()).string();
	}

	return {};
}

void to_json(nlohmann::json& json, const ResourceManager& manager)
{
	json["BaseDir"] = manager._baseDir;
	json["Resources"] = nlohmann::json::array();
	auto& jsonResources = json["Resources"];
	for (const auto& resource : manager._resources)
	{
		if (resource.first == ResourceManager::sResourceRegistryName)
		{
			continue;
		}

		jsonResources.push_back({{"Tag", resource.first},
								 {"Path", resource.second->GetDesc().GetPath()},
								 {"Type", resource.second->GetResourceType()}});
	}
}

void from_json(const nlohmann::json& json, ResourceManager& manager)
{
	if (json.contains("BaseDir") && json["BaseDir"].is_string())
	{
		manager._baseDir = json["BaseDir"].get<std::string>();
	}

	for (const auto& resource : json["Resources"])
	{
		if (!resource.contains("Tag") || !resource.contains("Path") || !resource.contains("Type"))
		{
			continue;
		}

		auto tag = resource["Tag"].get<std::string>();
		auto path = resource["Path"].get<std::string>();
		auto type = resource["Type"].get<std::string>();

		if (!tag.empty() && !path.empty() && !type.empty())
		{
			if (Resource* resPrototype = manager.FindSupportedType(type))
			{
				manager.AddResource(tag, resPrototype, {path});
			}
		}
	}
}