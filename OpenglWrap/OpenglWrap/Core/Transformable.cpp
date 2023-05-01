#include "Transformable.h"
#include <glm/gtx/transform.hpp>

void Transformable::SetLocation(const glm::vec3& loc)
{
	_location = loc;
	bWasChange = true;
}

void Transformable::SetRotation(const glm::vec3& rotation)
{
	_rotation = rotation;
	bWasChange = true;
}

void Transformable::SetScale(const glm::vec3& scale)
{
	_scale = scale;
	bWasChange = true;
}

void Transformable::Move(const glm::vec3& loc)
{
	_location += loc;
	bWasChange = true;
}

void Transformable::Rotate(const glm::vec3& rotation)
{
	_rotation += rotation;
	bWasChange = true;
}

void Transformable::Scale(const glm::vec3& scale)
{
	_scale += scale;
	bWasChange = true;
}

void Transformable::RequestMatrixUpdate()
{
	if (!bWasChange)
		return;

	_matrix = UpdateMatrix();
	bWasChange = false;
}

glm::mat4 Transformable::UpdateMatrix() const
{
	auto m = translate(glm::mat4(1.f), _location);
	m = rotate(m, _rotation.x, {1, 0, 0});
	m = rotate(m, _rotation.y, {0, 1, 0});
	m = rotate(m, _rotation.z, {0, 0, 1});
	m = scale(m, _scale);

	return m;
}
