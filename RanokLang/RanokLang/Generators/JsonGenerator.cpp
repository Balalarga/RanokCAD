#include "JsonGenerator.h"

void JsonGenerator::ProcessNode(std::stringstream& outCode, const FunctionDeclarationNode* node)
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

JsonGeneratorFunctionObject JsonGenerator::FlushObject()
{
	JsonGeneratorFunctionObject objectsCopy = _object;
	_object = {};
	return objectsCopy;
}
