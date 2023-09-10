#include "ModelItem.h"

#include "RanokLang/Lexer.h"
#include "RanokLang/Parser.h"


ModelTree ModelTree::sDefaultTree;


ShaderGenerator ModelItem::sGenerator;

ModelItem& ModelItem::SetCode(const std::string& newCode, bool* bSucceeded)
{
	Parser parser;
	const ActionTree newProgram = parser.Parse(Lexer{ newCode });
	if (!parser.HasErrors() && newProgram.Root())
	{
		_program = newProgram;
		_code = newCode;
		
		if (bSucceeded)
			*bSucceeded = true;
	}
	else if (bSucceeded)
	{
		*bSucceeded = false;
	}

	return *this;
}

std::optional<std::string> ModelItem::GetShaderCode() const
{
	return sGenerator.Generate(_program);
}

bool ModelTree::DrawItem(ImGuiTreeNodeFlags flags)
{
	if (ImGui::TreeNodeEx(GetInner().GetName().c_str(), flags))
	{
		return true;
	}

	return false;
}

