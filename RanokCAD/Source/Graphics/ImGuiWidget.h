#pragma once

class ImGuiWidget
{
public:
	ImGuiWidget() = default;
	virtual ~ImGuiWidget() = default;

	virtual void DrawGui() = 0;
};
