#pragma once
#include <filesystem>
#include <string>


class FileUtils
{
public:
	FileUtils() = delete;
	FileUtils(FileUtils&&) = delete;
	FileUtils(const FileUtils&) = delete;

	static std::filesystem::path GetWorkingDir() { return std::filesystem::current_path(); }

	static std::string GetRelativePath(const std::string& base, const std::string& target);
	static std::filesystem::path GetRelativePath(const std::filesystem::path& base, const std::filesystem::path& target);

	static std::shared_ptr<std::ifstream> CreateFileReader(const std::string& filepath);
	static std::shared_ptr<std::ofstream> CreateFileWriter(const std::string& filepath);

	static bool IsFileExists(const std::string& filepath);
};