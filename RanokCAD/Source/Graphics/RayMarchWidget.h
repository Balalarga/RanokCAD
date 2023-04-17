#pragma once
#include <memory>
#include <string>

#include "FboWidget.h"

class SceneObject;
class Material;

class RayMarchWidget: public FboWidget
{
public:
	RayMarchWidget(glm::ivec2 size, int channels);

	void UpdateCode(const std::string& fragmentCode);

	void Render();

	void DrawGui() override;


protected:
	std::shared_ptr<Material> _material;
	std::shared_ptr<SceneObject> _obj;
};
