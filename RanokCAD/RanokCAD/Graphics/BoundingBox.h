#pragma once
#include "OpenglWrap/Core/SceneObject.h"

class BoundingBox: public SceneObject
{
public:
	BoundingBox(glm::vec3 scale, std::shared_ptr<Material> material);

	void Render() override;

private:
	glm::vec3 _boxVertices[4];
};
