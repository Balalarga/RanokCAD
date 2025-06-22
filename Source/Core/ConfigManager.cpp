#include "ConfigManager.h"

#include <utility>


ConfigManager& ConfigManager::SystemConfigManager()
{
	static ConfigManager systemManager(RCAD_CONFIG_DIR);
	return systemManager;
}

ConfigManager& ConfigManager::UserConfigManager()
{
	static ConfigManager systemManager(std::filesystem::current_path() / "Config");
	return systemManager;
}

ConfigManager::ConfigManager(std::filesystem::path rootDir)
	: _rootDir(std::move(rootDir))
{
}

// void ConfigManager::SetRootDir(std::string_view path) {
// 	_rootDir = path;
// }

const std::filesystem::path& ConfigManager::GetRootDir() const
{
	return _rootDir;
}
