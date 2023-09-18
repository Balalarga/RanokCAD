#pragma once
#include <memory>
#include <string>

#include "FboWidget.h"
#include "Modules/Development/Model/AssemblyPart.h"
#include "OpenglWrap/Camera.h"

class BoundingBox;
class SceneObject;
class Material;


class RayMarchWidget: public FboWidget
{
	friend class RanokCADApp;
public:
	RayMarchWidget(glm::ivec2 size);
	virtual ~RayMarchWidget();

	void SetObjects(const std::vector<std::unique_ptr<AssemblyPart>>& objects);
	void SetUniforms(const std::vector<std::unique_ptr<AssemblyPart>>& objects) const;
	
	void UpdateCode(const std::string& fragmentCode);

	void Render();

	void DrawGui() override;

	Camera& GetCamera() { return _camera; }


protected:
	Camera _camera;
	std::shared_ptr<Material> _material;
	std::shared_ptr<SceneObject> _obj;

	std::shared_ptr<Material> _materialFwd;
	std::shared_ptr<BoundingBox> _objFwd;
};
