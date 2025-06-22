#pragma once
#include <string>
#include "argparse/argparse.hpp"


class AppArgs
{
public:
	AppArgs(const AppArgs&) = delete;
	AppArgs(AppArgs&&) = delete;
	AppArgs& operator=(const AppArgs&) = delete;


	static AppArgs& Get();

	static void SetAppName(const std::string& appName);
	static bool Init(int argc, char** argv);

	template <class T>
	static std::optional<T> Value(const std::string_view argName)
	{
		return GetParser().present(argName);
	}

	static argparse::ArgumentParser& GetParser();


private:
	static std::string _sAppName;

	argparse::ArgumentParser _argParser;


	AppArgs();
};
