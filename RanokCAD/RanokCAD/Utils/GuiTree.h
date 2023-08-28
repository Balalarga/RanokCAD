#pragma once
#include <string>
#include <vector>

#include "Graphics/ImGuiWidget.h"
#include "ImGui/imgui.h"


template<class T>
class GuiTree: public ImGuiWidget
{
public:
	GuiTree(T val = T())
		: _val(std::move(val))
	{
	}

	void DrawGui() override
	{
		if (_bOpened)
			_flags |= ImGuiTreeNodeFlags_DefaultOpen;

		_bOpened = ImGui::TreeNodeEx(GetTitle().c_str(), _flags);
		if (_bOpened)
		{
			DrawItem();
			for (GuiTree& child : _children)
				child.DrawGui();

			ImGui::TreePop();
		}
	}

	void SetOpened(bool opened)
	{
		_bOpened = opened;
	}

	virtual void DrawItem() = 0;
	virtual std::string GetTitle() const = 0;

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


private:
	ImGuiTreeNodeFlags _flags = ImGuiTreeNodeFlags_None;
	bool _bOpened = false;

	T _val;
	std::vector<GuiTree> _children;
	std::string _depthIds;
};

