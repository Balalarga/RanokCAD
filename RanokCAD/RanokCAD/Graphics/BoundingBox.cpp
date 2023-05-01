#include "BoundingBox.h"

#include <utility>

static std::vector<glm::vec3> shapeObjData{
	{-1, -1, 0},
	{-1, 1, 0},
	{1, 1, 0},
	{1, -1, 0},
};

BoundingBox::BoundingBox(glm::vec3 scale, std::shared_ptr<Material> material) :
	SceneObject(LaidVramBuffer(RawPtrData(shapeObjData), VramBufferLayout().Float(3)), std::move(material))
{
	SetDrawType(DrawType::Quads);
	SetScale(scale);
	RequestMatrixUpdate();
}

void BoundingBox::Render()
{
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_LINE);
	SceneObject::Render();
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);
}
