#include "AssemblyCodeGenerator.h"

#include "AssemblyPart.h"

void AssemblyCodeGenerator::ProcessNode(std::stringstream& outCode, const FunctionDeclarationNode* node)
{
	if (node->Name() == "main" && !ActionNode::IsArray(node->Body()))
	{
		const std::vector<VariableDeclarationNode*>& sigArgs = node->Signature().Args();
		_object.args.resize(sigArgs.size());
		for (size_t i = 0; i < sigArgs.size(); ++i)
		{
			_object.args[i].name = sigArgs[i]->Name();
			_object.args[i].type = "float";
			if (const ArrayNode* asArr = ActionNode::IsArray(sigArgs[i]->Value()))
				_object.args[i].count = asArr->Values().size();
			else
				_object.args[i].count = 1;
		}
		outCode << "{\n";
		if (_object.args.size() == 1 && _part)
		{
			for (size_t i = 0; i < sigArgs.size(); ++i)
			{
				outCode << _object.args[0].name << "[" << i << "] = ";
				outCode << _object.args[0].name << "[" << i << "] + " << _part->GetName() << "Data.location["<<i<<"];\n"; 
			}
		}
		for (size_t i = sigArgs.size(); i < node->Factory().DeclarationOrder().size(); ++i)
			Process(outCode, node->Factory().DeclarationOrder()[i]);

		PrintIndent(outCode);
		outCode << "return ";
		Process(outCode, node->Body());
		outCode << ";\n}\n";
		_object.body = outCode.str();
		outCode.str("");
	}
}

JsonGeneratorFunctionObject AssemblyCodeGenerator::FlushObject()
{
	JsonGeneratorFunctionObject objectsCopy = _object;
	_object = {};
	return objectsCopy;
}

void AssemblyCodeGenerator::SetAssemblyPart(const AssemblyPart* part)
{
	_part = part;
}
