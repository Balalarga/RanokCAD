#pragma once
#include <vector>
#include "nlohmann/json.hpp"


struct AssemblyShaderCode
{
	std::vector<nlohmann::json> Objects;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(AssemblyShaderCode, Objects)
};
