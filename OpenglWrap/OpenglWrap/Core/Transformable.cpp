#include "Transformable.h"

#include <glm/gtx/transform.hpp>
#include <iostream>
#include <ostream>

void Transformable::SetLocation(const glm::vec3& loc)
{
	_location = loc;
	bWasChange = true;
}

void Transformable::SetRotation(const glm::vec3& rotation)
{
	_rotation = glm::radians(rotation);
	bWasChange = true;
}

void Transformable::SetScale(const glm::vec3& scale)
{
	_scale = scale;
	bWasChange = true;
}

glm::mat4 rotationX(float angle)
{
	return glm::mat4(1.0, 0, 0, 0, 0, cos(angle), -sin(angle), 0, 0, sin(angle), cos(angle), 0, 0, 0, 0, 1);
}

glm::mat4 rotationY(float angle)
{
	return glm::mat4(cos(angle), 0, sin(angle), 0, 0, 1.0, 0, 0, -sin(angle), 0, cos(angle), 0, 0, 0, 0, 1);
}

glm::mat4 rotationZ(float angle)
{
	return glm::mat4(cos(angle), -sin(angle), 0, 0, sin(angle), cos(angle), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
}

glm::vec3 rotate(glm::vec3 a, glm::vec3 rotation)
{
	const glm::vec4 res(glm::vec4(a, 1.0) * rotationY(rotation.x) * rotationX(rotation.y) * rotationZ(rotation.z));
	return glm::vec3(res);
}

void Transformable::Move(const glm::vec3& loc)
{
	const glm::vec3 rotatedLoc = rotate(loc, _rotation);
	_location += rotatedLoc;
	bWasChange = true;
}

void Transformable::Rotate(const glm::vec3& rotation)
{
	_rotation += glm::radians(rotation);
	bWasChange = true;
}

void Transformable::Scale(const glm::vec3& scale)
{
	_scale += scale;
	bWasChange = true;
}

const glm::mat4& Transformable::GetUpdatedMatrix()
{
	RequestMatrixUpdate();
	return _matrix;
}

void Transformable::RequestMatrixUpdate()
{
	if (!bWasChange)
		return;

	_matrix = UpdateMatrix();
	bWasChange = false;
}

glm::mat4 Transformable::UpdateMatrix()
{
	auto m = glm::mat4(1.f);
	m = rotate(m, (_rotation.x), {1, 0, 0});
	m = rotate(m, (_rotation.y), {0, 1, 0});
	m = rotate(m, (_rotation.z), {0, 0, 1});
	m = translate(m, _location);
	m = scale(m, _scale);

	return m;
}
