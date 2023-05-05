#include "BoundingBox.h"

#include <utility>

static std::vector<glm::vec3> shapeObjData{
	{-1, -1, 0},
	{-1, 1, 0},
	{1, 1, 0},
	{1, -1, 0},
};

BoundingBox::BoundingBox(glm::vec3 scale, std::shared_ptr<Material> material) :
	SceneObject(LaidVramBuffer(RawPtrData(&_boxVertices, 4, sizeof glm::vec3), VramBufferLayout().Float(3)), std::move(material)),
	_boxVertices{{-scale.x, -scale.y, 0}, {-scale.x, scale.y, 0}, {scale.x, scale.y, 0}, {scale.x, -scale.y, 0}}
{
	SetDrawType(DrawType::Quads);
	// TODO: Model matrix in shader
	// SetScale(scale);
	// RequestMatrixUpdate();
}

void BoundingBox::Render()
{
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_LINE);
	SceneObject::Render();
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);
}
