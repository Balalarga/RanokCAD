#pragma once

#include "Application.h"
#include "Graphics/FboWidget.h"

class RanokCADApp: public Application
{
public:
	RanokCADApp();

	void Render() override;

	void RenderImGui() override;

	void Update(float delta) override;

	FboWidget widget;
};