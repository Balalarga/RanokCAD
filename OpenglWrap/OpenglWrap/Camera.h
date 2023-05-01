#pragma once
#include "Core/Transformable.h"


class Camera: public Transformable
{
public:
	Camera(float fov, float aspect, float near, float far);


protected:
	glm::mat4 UpdateMatrix() const override;


private:
	float _fov;
	float _aspect;
	float _near;
	float _far;
};
