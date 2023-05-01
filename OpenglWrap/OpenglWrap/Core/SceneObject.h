﻿#pragma once
#include <memory>

#include "LaidVramBuffer.h"
#include "Transformable.h"
#include "VramHandle.h"

class Material;

enum class DrawType
{
	Points = GL_POINTS,
	LineStrip = GL_LINE_STRIP,
	LineLoop = GL_LINE_LOOP,
	Lines = GL_LINES,
	LineStripAdjacency = GL_LINE_STRIP_ADJACENCY,
	LinesAdjacency = GL_LINES_ADJACENCY,
	TriangleStrip = GL_TRIANGLE_STRIP,
	TriangleFan = GL_TRIANGLE_FAN,
	Triangles = GL_TRIANGLES,
	TriangleStripAdjacency = GL_TRIANGLE_STRIP_ADJACENCY,
	TriangleAdjacency = GL_TRIANGLES_ADJACENCY,
	Quads = GL_QUADS,
	Patches = GL_PATCHES
};

class SceneObject: public VramHandle, public Transformable
{
public:
	SceneObject(LaidVramBuffer buffer, std::shared_ptr<Material> material);
	virtual ~SceneObject();

	virtual void Render();
	virtual void Update(float time);

	void SetDrawType(DrawType type);
	DrawType GetDrawType() const
	{
		return static_cast<DrawType>(_drawType);
	}

	std::shared_ptr<Material> GetMaterial() const
	{
		return _material;
	}

	virtual void SetupUniforms(Material& material);


protected:
	bool Init() override;

	int AllocateVram() override;
	void DeallocateVram() override;


private:
	LaidVramBuffer _buffer;
	std::shared_ptr<Material> _material;

	unsigned _drawType;
};
