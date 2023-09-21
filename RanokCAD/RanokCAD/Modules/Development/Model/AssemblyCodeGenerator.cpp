#include "AssemblyCodeGenerator.h"

#include "Model.h"

void AssemblyCodeGenerator::ProcessNode(std::stringstream& outCode, const FunctionDeclarationNode* node)
{
	if (node->Name() == "main" && !ActionNode::IsArray(node->Body()))
	{
		const std::vector<VariableDeclarationNode*>& sigArgs = node->Signature().Args();
		_object.Args.resize(sigArgs.size());
		for (size_t i = 0; i < sigArgs.size(); ++i)
		{
			_object.Args[i].Name = sigArgs[i]->Name();
			_object.Args[i].Type = "float";
			if (const ArrayNode* asArr = ActionNode::IsArray(sigArgs[i]->Value()))
				_object.Args[i].Count = asArr->Values().size();
			else
				_object.Args[i].Count = 1;
		}
		outCode << "{\n";
		for (size_t i = sigArgs.size(); i < node->Factory().DeclarationOrder().size(); ++i)
			Process(outCode, node->Factory().DeclarationOrder()[i]);

		PrintIndent(outCode);
		outCode << "return ";
		Process(outCode, node->Body());
		outCode << ";\n}\n";
		_object.Body = outCode.str();
		outCode.str("");
	}
}

JsonGeneratorFunctionObject AssemblyCodeGenerator::FlushObject()
{
	JsonGeneratorFunctionObject objectsCopy = _object;
	_object = {};
	return objectsCopy;
}
