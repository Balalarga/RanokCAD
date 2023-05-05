#include "Camera.h"

#include <glm/gtx/transform.hpp>

Camera::Camera(float fov, float aspect, float near, float far) : _fov(fov), _aspect(aspect), _near(near), _far(far)
{
	// SetRotation({0, 0, 90});
	// RequestMatrixUpdate();
}

glm::mat4 Camera::UpdateMatrix() const
{
	auto m = translate(glm::mat4(1.f), GetLocation());
	m = rotate(m, glm::radians(GetRotation().x), {1, 0, 0});
	m = rotate(m, glm::radians(GetRotation().y), {0, 1, 0});
	m = rotate(m, glm::radians(GetRotation().z), {0, 0, 1});
	m = glm::perspective(_fov, _aspect, _near, _far) * m;

	return m;
}
