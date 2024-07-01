#include "GpuBuffer.h"


GpuBufferLayout& GpuBufferLayout::Float(unsigned int count)
{
	_variables.push_back({GL_FLOAT, count, sizeof(GLfloat)});
	TotalSize += count * sizeof(GLfloat);
	return *this;
}

GpuBufferLayout& GpuBufferLayout::Int(unsigned int count)
{
	_variables.push_back({GL_INT, count, sizeof(GLint)});
	TotalSize += count * sizeof(GLint);
	return *this;
}

GpuBufferLayout& GpuBufferLayout::Unsigned(unsigned int count)
{
	_variables.push_back({GL_UNSIGNED_INT, count, sizeof(GLuint)});
	TotalSize += count * sizeof(GLuint);
	return *this;
}

const std::vector<GpuBufferLayout::Variable>& GpuBufferLayout::Variables() const
{
	return _variables;
}
