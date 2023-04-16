#include "SceneObject.h"

#include <utility>

#include "Material.h"

SceneObject::SceneObject(LaidVramBuffer buffer, std::shared_ptr<Material> material, bool bAutoInit):
	_buffer(std::move(buffer)),
	_material(std::move(material)),
	_drawType(GL_TRIANGLES)
{
	if (bAutoInit)
		SceneObject::Init();
}

bool SceneObject::Init()
{
	if (!VramHandle::Init())
		return false;

	glBindVertexArray(GetHandle());

	const unsigned vboId = _buffer.MakeCopyToVram();

	glBindVertexArray(0);

	glDeleteBuffers(1, &vboId);

	return true;
}

void SceneObject::Render()
{
	UpdateMatrix();
	glBindVertexArray(GetHandle());
	glDrawArrays(_drawType, 0, _buffer.GetCount());
}

void SceneObject::Update(float time)
{
}

void SceneObject::SetDrawType(DrawType type)
{
	_drawType = static_cast<unsigned>(type);
}

void SceneObject::SetupUniforms(Material& material)
{
}

int SceneObject::AllocateVram()
{
	unsigned vao = 0;

	glGenVertexArrays(1, &vao);

	return static_cast<int>(vao);
}

void SceneObject::DeallocateVram()
{
	auto vao = static_cast<unsigned>(GetHandle());
	glDeleteVertexArrays(1, &vao);
}
