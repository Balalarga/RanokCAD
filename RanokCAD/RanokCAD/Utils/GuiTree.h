#pragma once
#include <string>
#include <vector>

#include "Graphics/ImGuiWidget.h"
#include "ImGui/imgui.h"

template<class T>
class GuiTree: public ImGuiWidget
{
public:
	GuiTree(T val = T()) : _val(std::move(val))
	{
	}

	void DrawGui() override
	{
		ImGuiTreeNodeFlags runtimeFlags = ImGuiTreeNodeFlags_None;
		if (_bOpened)
			runtimeFlags |= ImGuiTreeNodeFlags_DefaultOpen;
		
		if (_children.empty())
			runtimeFlags |= ImGuiTreeNodeFlags_Leaf;
		
		_bOpened = DrawItem(_flags | runtimeFlags);
		if (_bOpened)
		{
			for (GuiTree& child : _children)
				child.DrawGui();
			
			ImGui::TreePop();
		}
	}

	void SetOpened(bool opened)
	{
		_bOpened = opened;
	}

	virtual bool DrawItem(ImGuiTreeNodeFlags flags)
	{
		return ImGui::TreeNodeEx(GetTitle().c_str(), flags);
	}

	virtual std::string GetTitle() const
	{
		return "<UnnamedTree>";
	}

	void AddFlag(ImGuiTreeNodeFlags flag)
	{
		_flags |= flag;
	}

	void SetFlag(ImGuiTreeNodeFlags flag)
	{
		_flags = flag;
	}

	void RemoveFlag(ImGuiTreeNodeFlags flag)
	{
		_flags &= !flag;
	}

	const T& GetInner() const
	{
		return _val;
	}


protected:
	const std::vector<GuiTree>& GetChildren() const
	{
		return _children;
	}


private:
	ImGuiTreeNodeFlags _flags = ImGuiTreeNodeFlags_None;
	bool _bOpened = false;

	T _val;
	std::vector<GuiTree> _children;
	std::string _depthIds;
};
