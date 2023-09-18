#pragma once

class IImGuiWidget
{
public:
	IImGuiWidget() = default;
	virtual ~IImGuiWidget() = default;

	virtual void DrawGui() = 0;
};
