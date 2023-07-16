#include "FileUtils.h"


#include <fstream>

using namespace std::filesystem;

std::string FileUtils::GetRelativePath(const std::string& base, const std::string& target)
{
	return GetRelativePath(path{ base }, path{ target }).string();
}

path FileUtils::GetRelativePath(const path& base, const path& target)
{
	return relative(target, base);
}

std::shared_ptr<std::ifstream> FileUtils::CreateFileReader(const std::string& filepath)
{
	auto stream = std::make_shared<std::ifstream>(filepath);
	if (stream->is_open())
		return stream;

	return nullptr;
}

std::shared_ptr<std::ofstream> FileUtils::CreateFileWriter(const std::string& filepath)
{
	auto stream = std::make_shared<std::ofstream>(filepath);
	if (stream->is_open())
		return stream;

	return nullptr;
}

bool FileUtils::IsFileExists(const std::string& filepath)
{
	return is_regular_file(filepath);
}

std::vector<path> FileUtils::ScanDir(const path& dir, bool bRecursive)
{
	std::vector<path> files;
	if (!exists(dir))
		return files;

	if (bRecursive)
	{
		for (auto& entry : recursive_directory_iterator(dir))
			files.push_back(entry.path());
	}
	else
	{
		for (auto& entry : directory_iterator(dir))
			files.push_back(entry.path());
	}


	return files;
}
