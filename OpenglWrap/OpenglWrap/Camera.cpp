#include "Camera.h"

#include <glm/ext/matrix_clip_space.hpp>

Camera::Camera(float fov, float aspect, float near, float far) : _fov(fov), _aspect(aspect), _near(near), _far(far)
{
	// SetRotation({0, 0, 40});
	// RequestMatrixUpdate();
}

glm::mat4 Camera::UpdateMatrix() const
{
	auto m = Transformable::UpdateMatrix();

	m = glm::perspective(_fov, _aspect, _near, _far) * m;

	return m;
}
