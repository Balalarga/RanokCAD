#pragma once
#include "argparse/argparse.hpp"
#include <optional>
#include <string>

class AppArgs {
public:
	AppArgs(const AppArgs&) = delete;
	AppArgs(AppArgs&&) = delete;
	AppArgs& operator=(const AppArgs&) = delete;

	static AppArgs& Get();

	static void SetAppName(std::string_view appName);
	static bool Init(int argc, char** argv, std::function<void(argparse::ArgumentParser&)>&& argsSetup);
	static bool Init(
		std::string_view appName
		, int argc
		, char** argv
		, std::function<void(argparse::ArgumentParser&)>&& argsSetup);

	template <class T>
	static std::optional<T> Value(std::string_view argName)
	{
		return GetParser().present(argName);
	}

	static bool Parse(std::string_view argName);

	static argparse::ArgumentParser& GetParser();


private:
	AppArgs() = default;

	static std::string _sAppName;

	argparse::ArgumentParser _argParser;
};
