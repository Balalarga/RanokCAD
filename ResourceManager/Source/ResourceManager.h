#pragma once
#include <filesystem>
#include <map>
#include <memory>
#include <string>

#include "Resources/Resource.h"
#include "nlohmann/json.hpp"

class ResourceManager
{
	friend void to_json(nlohmann::json& json, const ResourceManager& manager);
	friend void from_json(const nlohmann::json& json, ResourceManager& manager);

public:
	static const std::string sResourceRegistryName;

	ResourceManager();
	ResourceManager(ResourceManager&&) = delete;
	ResourceManager(const ResourceManager&) = delete;

	virtual ~ResourceManager();

	virtual void AddDefaultSupportedResources();
	bool InitFrom(const std::string& configPath);
	bool Save(const std::string& configPath = {}) const;

	template<class T>
	requires std::is_base_of_v<Resource, T> ResourceManager& AddSupportedResourceType()
	{
		T* res = new T(ResourceDesc::GetEmptyDesc());
		_supportedTypes[res->GetResourceType()] = std::unique_ptr<Resource>(res);
		return *this;
	}

	Resource* FindSupportedType(const std::string& name);

	Resource* AddResource(const std::string& tag, Resource* proto, const ResourceDesc& desc);

	template<class T, class... TArgs>
	requires std::is_base_of_v<Resource, T> T* AddResource(const std::string& tag, const ResourceDesc& desc)
	{
		if (GetResource(tag))
			return nullptr;

		if (auto proto = FindSupportedType(T(ResourceDesc::GetEmptyDesc()).GetResourceType()))
			return static_cast<T*>(AddResource(tag, proto, desc));

		return nullptr;
	}

	template<class T>
	requires std::is_base_of_v<Resource, T> T* GetResource(const std::string& tag) const
	{
		Resource* res = GetResource(tag);
		if (res && res->GetResourceType() == T(ResourceDesc::GetEmptyDesc()).GetResourceType())
			return static_cast<T*>(res);

		return nullptr;
	}

	template<class T, class... TArgs>
	requires std::is_base_of_v<Resource, T> T* GetOrAddResource(const std::string& tag, const ResourceDesc& desc)
	{
		if (auto proto = FindSupportedType(T(ResourceDesc::GetEmptyDesc()).GetResourceType()))
		{
			return static_cast<T*>(GetOrAddResource(tag, proto, desc));
		}

		return nullptr;
	}

	Resource* GetResource(const std::string& tag) const;
	Resource* GetOrAddResource(const std::string& tag, Resource* proto, const ResourceDesc& desc);

	int LoadAll(std::vector<std::shared_ptr<Resource>>* failed = nullptr) const;
	bool LoadResource(Resource* resource) const;
	bool LoadResource(const std::string& tag) const;

	bool SaveResource(Resource* resource) const;
	bool SaveResource(const std::string& tag) const;

	std::string GetResourcePath(const std::string& tag) const;
	std::string GetResourcePath(const Resource* res) const;


private:
	std::filesystem::path _baseDir;
	std::filesystem::path _configPath;

	std::map<std::string, std::unique_ptr<Resource>> _supportedTypes;

	std::map<std::string, std::shared_ptr<Resource>> _resources;

	std::vector<std::shared_ptr<Resource>> _resourcesArray;
};