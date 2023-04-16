#pragma once
#include <vector>

#include <GL/glew.h>

#include "RawPtrData.h"
#include "VramBufferLayout.h"


template <typename T>
concept HaveVramBufferLayout = requires(T v)
{
	{ T::GetVramBufferLayout() } -> std::convertible_to<VramBufferLayout>;
};


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


class LaidVramBuffer
{
public:
	LaidVramBuffer(const RawPtrData& data, VramBufferLayout layout);

	template<HaveVramBufferLayout T>
	LaidVramBuffer(const std::initializer_list<T>& data):
		LaidVramBuffer(RawPtrData(data), T::GetVramBufferLayout())
	{
	}

	template<HaveVramBufferLayout T>
	LaidVramBuffer(const std::vector<T>& data):
		LaidVramBuffer(RawPtrData(data), T::GetVramBufferLayout())
	{
	}

	void Set(UsageMode mode);
	void Set(BufferType type);

	BufferType GetBufferType() const { return static_cast<BufferType>(_type); }
	UsageMode GetUsageMode() const { return static_cast<UsageMode>(_usageMode); }

	unsigned MakeCopyToVram();

	int GetCount() const { return static_cast<int>(_data.Count); }


private:
	const RawPtrData _data;
	const VramBufferLayout _layout;

	unsigned _type;
	unsigned _usageMode;
};
