#include "Camera.h"

#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/transform.hpp>

Camera::Camera(float fov, float aspect, float near, float far) : _fov(fov), _aspect(aspect), _near(near), _far(far)
{
	// SetRotation({0, 0, 90});
	// RequestMatrixUpdate();
}

glm::mat4 Camera::UpdateMatrix()
{
	glm::mat4 projMat = glm::perspective(_fov, _aspect, _near, _far);
	auto forwardVector = glm::rotate(_baseForwardVector, glm::radians(GetRotation().x), {1, 0, 0});
	forwardVector = glm::rotate(forwardVector, glm::radians(GetRotation().y), {0, 1, 0});
	forwardVector = glm::rotate(forwardVector, glm::radians(GetRotation().z), {0, 0, 1});
	glm::mat4 viewMat = glm::lookAt(GetLocation(), GetLocation() + forwardVector, _upVector);

	return projMat * viewMat;
}
