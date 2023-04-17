#pragma once
#include <memory>

#include "Graphics/FboWidget.h"
#include "IModule.h"

class DevelopmentModule: public IModule
{
public:
	DevelopmentModule();

	void DrawGui() override;


private:
	std::shared_ptr<FboWidget> _viewport;
};
