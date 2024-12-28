#include "AppArgs.h"
#include "spdlog/spdlog.h"


std::string AppArgs::_sAppName = "RanokCAD";


void AppArgs::SetAppName(const std::string& appName)
{
	_sAppName = appName;
}

AppArgs& AppArgs::Get()
{
	static AppArgs inst;
	return inst;
}

bool AppArgs::Init(int argc, char** argv)
{
	try
	{
		GetParser().parse_args(argc, argv);

		return true;
	}
	catch (const std::exception& error)
	{
		spdlog::critical(error.what());
		return false;
	}
}

AppArgs::AppArgs()
	: _argParser(_sAppName)
{
}

argparse::ArgumentParser& AppArgs::GetParser()
{
	return Get()._argParser;
}