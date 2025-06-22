#pragma once
#include <fstream>
#include <string_view>
#include "nlohmann/json.hpp"
#include "spdlog/spdlog.h"


class ConfigManager {
public:
	static ConfigManager& SystemConfigManager();
	static ConfigManager& UserConfigManager();


	explicit ConfigManager(std::filesystem::path rootDir);
	ConfigManager(const ConfigManager&) = delete;
	ConfigManager(ConfigManager&&) = delete;
	ConfigManager& operator=(const ConfigManager&) = delete;


	template <class T>
	std::optional<T> TryRead(std::string_view path)
	{
		std::ifstream file(_rootDir / path);
		if (!file) {
			return std::nullopt;
		}

		T config = nlohmann::json::parse(file);
		file.close();
		return config;
	}

	template <class T>
	std::optional<T> Read(std::string_view path)
	{
		auto res = TryRead<T>(path);
		if (!res)
			spdlog::error("Failed to read config from '{}'", _rootDir / path);
		return res;
	}

	template <class T>
	bool TrySave(T&& obj, std::string_view path, int indent = 4)
	{
		const auto fullPath = _rootDir / path;
		create_directories(fullPath.parent_path());
		std::ofstream file(fullPath);
		if (!file)
			return false;

		nlohmann::json defaultObj = T{};
		auto diffJson = nlohmann::json::diff(defaultObj, obj);
		file << nlohmann::json({}).patch(diffJson).dump(indent);
		file.close();
		return true;
	}

	template <class T>
	bool Save(T&& obj, std::string_view path, int indent = 4)
	{
		auto res = TrySave<T>(obj, path, indent);
		if (!res)
			return false;

		return res;
	}


	// void SetRootDir(std::string_view path);
	const std::filesystem::path& GetRootDir() const;


private:
	std::filesystem::path _rootDir;
};
