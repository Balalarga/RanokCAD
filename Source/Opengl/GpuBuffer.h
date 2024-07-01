#pragma once

#include <vector>
#include "GpuResource.h"
#include "gl/glew.h"


enum class BufferType
{
	Array = GL_ARRAY_BUFFER,
	ElementArray = GL_ELEMENT_ARRAY_BUFFER,
	CopyRead = GL_COPY_READ_BUFFER,
	CopyWrite = GL_COPY_WRITE_BUFFER,
	Texture = GL_TEXTURE_BUFFER,
	Uniform = GL_UNIFORM_BUFFER,
	Query = GL_QUERY_BUFFER
};

enum class UsageMode
{
	StreamDraw = GL_STREAM_DRAW,
	StreamRead = GL_STREAM_READ,
	StreamCopy = GL_STREAM_COPY,
	StaticDraw = GL_STATIC_DRAW,
	StaticRead = GL_STATIC_READ,
	StaticCopy = GL_STATIC_COPY,
	DynamicDraw = GL_DYNAMIC_DRAW,
	DynamicRead = GL_DYNAMIC_READ,
	DynamicCopy = GL_DYNAMIC_COPY
};


class GpuBufferLayout
{
public:
	struct Variable
	{
		unsigned Type;
		unsigned Num;
		unsigned Size;
		bool Normalized = true;
	};

	GpuBufferLayout& Float(unsigned count);
	GpuBufferLayout& Int(unsigned count);
	GpuBufferLayout& Unsigned(unsigned count);

	const std::vector<Variable>& Variables() const;

private:
	std::vector<Variable> _variables;
	unsigned TotalSize = 0;
};


class GpuBuffer: public GpuResource
{
};
