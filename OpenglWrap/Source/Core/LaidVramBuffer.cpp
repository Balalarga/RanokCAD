#include "LaidVramBuffer.h"
#include "GL/glew.h"

LaidVramBuffer::LaidVramBuffer(const RawPtrData& data, VramBufferLayout layout):
	_data(data),
	_layout(std::move(layout)),
	_type(GL_ARRAY_BUFFER),
	_usageMode(GL_STATIC_DRAW)
{
}

void LaidVramBuffer::Set(UsageMode mode)
{
	_usageMode = static_cast<unsigned>(mode);
}

void LaidVramBuffer::Set(BufferType type)
{
	_type = static_cast<unsigned>(type);
}

unsigned LaidVramBuffer::MakeCopyToVram()
{
	unsigned handle = 0;
	if (!_data.Ptr)
		return handle;

	glGenBuffers(1, &handle);
	glBindBuffer(_type, handle);
	glBufferData(_type, _data.Count * _data.ItemSize, _data.Ptr, _usageMode);

	long long offset = 0;
	for (int i = 0; i < _layout.Variables.size(); ++i)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i,
							  _layout.Variables[i].Count,
							  _layout.Variables[i].Type,
							  _layout.Variables[i].Normalized ? GL_FALSE : GL_TRUE,
							  _layout.Size,
							  (void*)offset);
		offset += _layout.Variables[i].Size * _layout.Variables[i].Count;
	}

	return handle;
}
