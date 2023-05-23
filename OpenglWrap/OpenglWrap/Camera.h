#pragma once
#include "Core/Transformable.h"

class Camera: public Transformable
{
public:
	Camera(float fov, float aspect, float near, float far);

	float GetFov() const
	{
		return _fov;
	}
	float GetAspect() const
	{
		return _aspect;
	}
	float GetNear() const
	{
		return _near;
	}
	float GetFar() const
	{
		return _far;
	}


protected:
	glm::mat4 UpdateMatrix() override;


private:
	float _fov;
	float _aspect;
	float _near;
	float _far;

	glm::vec3 _upVector{0, 1, 0};
	glm::vec3 _baseForwardVector{0, 0, 1};
};
