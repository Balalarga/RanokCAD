#pragma once

#include <glm/glm.hpp>


class Transformable
{
public:
	Transformable() = default;
	virtual ~Transformable() = default;

	void SetLocation(const glm::vec3& loc);
	void SetRotation(const glm::vec3& rotation);
	void SetScale(const glm::vec3& scale);

	void Move(const glm::vec3& loc);
	void Rotate(const glm::vec3& rotation);
	void Scale(const glm::vec3& scale);

	const glm::vec3& GetLocation() const { return _location; }
	const glm::vec3& GetRotation() const { return _rotation; }
	const glm::vec3& GetScale() const { return _scale; }

	const glm::mat4& GetMatrix() const { return _matrix; }
	void RequestMatrixUpdate();

protected:
	virtual glm::mat4 UpdateMatrix() const;

	glm::mat4& GetMutableMatrix() { return _matrix; }


private:
	glm::vec3 _location{0.f};
	glm::vec3 _rotation{0.f};
	glm::vec3 _scale{1.f};

	glm::mat4 _matrix{1.f};

	bool bWasChange{false};
};
