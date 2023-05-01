﻿#include "ShaderGenerator.h"

#include <format>
#include <sstream>

#include "RanokLang/Parser.h"

void ShaderGenerator::ProcessNode(std::stringstream& outCode, const BinaryNode* node)
{
	Token::Type type = node->GetToken().type;
	int currPriority = Parser::GetOperationPriority(type);
	int lPriority = Parser::GetOperationPriority(node->Left()->GetToken().type);
	int rPriority = Parser::GetOperationPriority(node->Right()->GetToken().type);
	bool needLeftParent = lPriority != -1 && lPriority < currPriority;
	bool needRightParent = rPriority != -1 && rPriority < currPriority;

	if (type == Token::Type::Hat)
	{
		outCode << "pow(";
	}
	else if (type == Token::Type::Ampersand)
	{
		outCode << "_rv_And(";
	}
	else if (type == Token::Type::Pipe)
	{
		outCode << "_rv_Or(";
	}

	if (needLeftParent)
	{
		outCode << "(";
		Process(outCode, node->Left());
		outCode << ")";
	}
	else
	{
		Process(outCode, node->Left());
	}

	if (type == Token::Type::Hat || type == Token::Type::Ampersand || type == Token::Type::Pipe)
	{
		outCode << ", ";
	}
	else
	{
		outCode << " " << node->Name() << " ";
	}

	if (needRightParent)
	{
		outCode << "(";
		Process(outCode, node->Right());
		outCode << ")";
	}
	else
	{
		Process(outCode, node->Right());
	}
	if (type == Token::Type::Hat || type == Token::Type::Ampersand || type == Token::Type::Pipe)
		outCode << ")";
}

void ShaderGenerator::ProcessNode(std::stringstream& outCode, const FunctionDeclarationNode* node)
{
	std::string nodeName;
	if (node->Name() != "main")
		nodeName = node->Name();
	else
		nodeName = "_main";
	const std::vector<VariableDeclarationNode*>& sigArgs = node->Signature().Args();
	if (const ArrayNode* arrBody = ActionNode::IsArray(node->Body()))
	{
		PrintIndent(outCode);
		constexpr const char* outVarName = "_out_name";
		outCode << std::format("void {}(", nodeName);
		for (size_t i = 0; i < sigArgs.size(); ++i)
		{
			if (const ArrayNode* arr = ActionNode::IsArray(sigArgs[i]))
				outCode << std::format("float {}[{}]", sigArgs[i]->Name(), arr->Values().size());
			else
				outCode << std::format("float {}", sigArgs[i]->Name());

			outCode << ", ";
		}
		outCode << "inout float " << outVarName << "[" << arrBody->Values().size() << "]";
		outCode << ")\n{\n";
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
	}
	else
	{
		outCode << std::format("float {}(", nodeName);
		for (size_t i = 0; i < sigArgs.size(); ++i)
		{
			if (const ArrayNode* asArr = ActionNode::IsArray(sigArgs[i]->Value()))
				outCode << std::format("float {}[{}]", sigArgs[i]->Name(), asArr->Values().size());
			else
				outCode << std::format("float {}", sigArgs[i]->Name());

			if (i + 1 != sigArgs.size())
				outCode << ", ";
		}
		outCode << ")\n{\n";
		for (size_t i = sigArgs.size(); i < node->Factory().DeclarationOrder().size(); ++i)
			Process(outCode, node->Factory().DeclarationOrder()[i]);

		PrintIndent(outCode);
		outCode << "return ";
		Process(outCode, node->Body());
		outCode << ";\n}\n";
	}
}