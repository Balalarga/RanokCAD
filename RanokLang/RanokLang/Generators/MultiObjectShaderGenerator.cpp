#include "MultiObjectShaderGenerator.h"

void MultiObjectShaderGenerator::ProcessNode(std::stringstream& outCode, const FunctionDeclarationNode* node)
{
	const std::vector<VariableDeclarationNode*>& sigArgs = node->Signature().Args();
	if (const ArrayNode* arrBody = ActionNode::IsArray(node->Body()))
	{
		nlohmann::json& place =
			node->Name() == "main" ? objectJson["Main"] : objectJson["Functions"].emplace_back(nlohmann::json{});
		place["Name"] = node->Name();
		for (size_t i = 0; i < sigArgs.size(); ++i)
		{
			nlohmann::json arg;
			arg["Name"] = sigArgs[i]->Name();
			arg["Type"] = "float";
			if (const ArrayNode* asArr = ActionNode::IsArray(sigArgs[i]->Value()))
				arg["Count"] = asArr->Values().size();
			place["Args"].push_back(arg);
		}
		place["ReturnType"] = "void";
		constexpr const char* outVarName = "_out_name";
		outCode << std::format("void {}(", node->Name());
		for (size_t i = 0; i < sigArgs.size(); ++i)
		{
			if (const ArrayNode* arr = ActionNode::IsArray(sigArgs[i]))
				outCode << std::format("float {}[{}]", sigArgs[i]->Name(), arr->Values().size());
			else
				outCode << std::format("float {}", sigArgs[i]->Name());

			outCode << ", ";
		}

		place["Args"].push_back({
			{"Name", outVarName},
			{"Type", "inout float"},
			{"Count", arrBody->Values().size()},
		});

		outCode << "{\n";
		for (size_t i = sigArgs.size(); i < node->Factory().DeclarationOrder().size(); ++i)
			Process(outCode, node->Factory().DeclarationOrder()[i]);

		std::string outResName = "_out_res";
		if (auto varRes = dynamic_cast<const VariableNode*>(node->Body()))
		{
			outResName = varRes->Name();
		}
		else
		{
			PrintIndent(outCode);
			outCode << "float " << outResName << "[" << arrBody->Values().size() << "] = ";
			Process(outCode, node->Body());
			outCode << ";\n";
		}
		PrintIndent(outCode);
		outCode << outVarName << " = " << outResName;
		outCode << ";\n}\n";
		place["Body"] = outCode.str();
		outCode.str("");
	}
	else
	{
		nlohmann::json& place =
			node->Name() == "main" ? objectJson["Main"] : objectJson["Functions"].emplace_back(nlohmann::json{});
		place["Name"] = node->Name();
		place["ReturnType"] = "float";

		for (size_t i = 0; i < sigArgs.size(); ++i)
		{
			nlohmann::json arg;
			arg["Name"] = sigArgs[i]->Name();
			arg["Type"] = "float";
			if (const ArrayNode* asArr = ActionNode::IsArray(sigArgs[i]->Value()))
				arg["Count"] = asArr->Values().size();
			place["Args"].push_back(arg);
		}
		outCode << "{\n";
		for (size_t i = sigArgs.size(); i < node->Factory().DeclarationOrder().size(); ++i)
			Process(outCode, node->Factory().DeclarationOrder()[i]);

		PrintIndent(outCode);
		outCode << "return ";
		Process(outCode, node->Body());
		outCode << ";\n}\n";
		place["Body"] = outCode.str();
		outCode.str("");
	}
}

nlohmann::json MultiObjectShaderGenerator::FlushJson()
{
	nlohmann::json res = objectJson;
	objectJson.clear();
	return res;
}

void MultiObjectShaderGenerator::SetColor(float r, float g, float b, float a)
{
	objectJson["Color"] = {
		{"r", r},
		{"g", g},
		{"b", b},
		{"a", a},
	};
}

void MultiObjectShaderGenerator::SetPosition(const glm::vec3& pos)
{
	objectJson["Pos"] = {
		{"x", pos.x},
		{"y", pos.y},
		{"z", pos.z},
	};
}
