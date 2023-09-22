#include "Assembly.h"

#include "AssemblyCodeGenerator.h"
#include "RanokLang/Parser.h"


Assembly::Assembly(std::string name)
	: IModelBase(std::move(name))
{
}

Assembly::Assembly(std::string name, std::vector<AssemblyPart> parts)
	: IModelBase(std::move(name))
	, _parts(std::move(parts))
{
}

void Assembly::AddPart(AssemblyPart&& part)
{
	_parts.emplace_back(std::move(part));
}

nlohmann::json Assembly::GenerateJson() const
{
	std::ostringstream combinationCode;

	for (const AssemblyPart& part : _parts)
		combinationCode << "def " << part.model.GetName() << "(s[3]){ return 0; };\n";

	combinationCode << "\ndef main(s[3]){\n";
	combinationCode << "return ";
	if (_parts.empty())
		combinationCode << "0";

	for (size_t i = 0; i < _parts.size(); ++i)
	{
		combinationCode << _parts[i].model.GetName() << "(s)";
		if ((i == 0 && _parts.size() < 2) || i != _parts.size() - 1)
			combinationCode << (_parts[i].combineType == AssemblyPart::CombineType::Subtract ? "&" : "|");
	}
	combinationCode << ";\n}";

	constexpr const char* baseArgName = "s";
	ActionTree newTree;
	FunctionDeclarationNode* func = newTree.GlobalFactory().CreateFunction(FunctionSignature({"main"}));
	ActionNodeFactory& mainFactory = func->Factory();
	func->Signature().Args().push_back(mainFactory.CreateVariable(
		Token{baseArgName},
		mainFactory.Create<ArrayNode>(
			Token{baseArgName},
			std::vector<ActionNode*>{
				nullptr,
				nullptr,
				nullptr,
			})));
	auto createSignature = [&](std::string&& name)
	{
		return FunctionSignature(
			{name},
			{
				mainFactory.CreateVariable(
					Token{baseArgName},
					mainFactory.Create<ArrayNode>(
						Token{baseArgName},
						std::vector<ActionNode*>{
							nullptr,
							nullptr,
							nullptr,
						})),
			});
	};
	
	VariableDeclarationNode* baseArg = mainFactory.FindVariable(baseArgName);
	for (const AssemblyPart& part : _parts)
	{
		const std::string varName = part.model.GetName() + "_loc";
		mainFactory.CreateVariable(
			Token{varName},
			mainFactory.Create<ArrayNode>(
				Token{varName},
				std::vector<ActionNode*>{
					mainFactory.Create<BinaryNode>(
						Token{"+"},
						mainFactory.Create<NamedNode>(std::vformat("{}_{}Data.location.x", std::make_format_args(GetName(), part.model.GetName()))),
						mainFactory.Create<ArrayGetterNode>(
							baseArg, mainFactory.Create<DoubleNumberNode>(Token{Token::Type::Number}, 0))),
					mainFactory.Create<BinaryNode>(
						Token{"+"},
						mainFactory.Create<NamedNode>(std::vformat("{}_{}Data.location.y", std::make_format_args(GetName(), part.model.GetName()))),
						mainFactory.Create<ArrayGetterNode>(
							baseArg, mainFactory.Create<DoubleNumberNode>(Token{Token::Type::Number}, 1))),
					mainFactory.Create<BinaryNode>(
						Token{"+"},
						mainFactory.Create<NamedNode>(std::vformat("{}_{}Data.location.z", std::make_format_args(GetName(), part.model.GetName()))),
						mainFactory.Create<ArrayGetterNode>(
							baseArg, mainFactory.Create<DoubleNumberNode>(Token{Token::Type::Number}, 2))),
				}));
	}

	ActionNode* body = nullptr;
	for (size_t i = 0; i < _parts.size(); ++i)
	{
		VariableDeclarationNode* modelLocationVar = mainFactory.FindVariable(_parts[i].model.GetName() + "_loc");
		if (body == nullptr)
		{
				body = mainFactory.Create<FunctionCallNode>(
					mainFactory.CreateFunction(
						createSignature(_parts[i].model.GetName()),
						mainFactory.Create<DoubleNumberNode>(Token(Token::Type::Number), 0)),
					std::vector<ActionNode*>{mainFactory.Create<VariableNode>(modelLocationVar)});
			
			continue;
		}

		body = mainFactory.Create<BinaryNode>(
				Token{_parts[i].combineType == AssemblyPart::CombineType::Subtract ? Token::Type::Ampersand : Token::Type::Pipe},
			body,
			mainFactory.Create<FunctionCallNode>(
				mainFactory.CreateFunction(
					createSignature(_parts[i].model.GetName()),
					mainFactory.Create<DoubleNumberNode>(Token(Token::Type::Number), 0)),
				std::vector<ActionNode*>{mainFactory.Create<VariableNode>(modelLocationVar)}));
	}
	func->SetBody(body);

	newTree.SetRoot(func);


	static AssemblyCodeGenerator generator;
	static Parser parser;
	ActionTree actionTree = parser.Parse(Lexer(combinationCode.str()));
	generator.Generate(newTree);

	nlohmann::json subModelsArr;
	for (const AssemblyPart& part : _parts)
		subModelsArr.push_back(part.model.GenerateJson());

	return {{"Name", GetName()}, {"Function", generator.FlushObject()}, {"Models", subModelsArr}};
}
