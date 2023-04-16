#include "VramBufferLayout.h"

#include <GL/glew.h>

VramBufferLayout& VramBufferLayout::Float(unsigned count)
{
	Variables.push_back({GL_FLOAT, count, sizeof(GLfloat)}); Size += count * sizeof(GLfloat);
	return *this;
}

VramBufferLayout& VramBufferLayout::Int(unsigned count)
{
	Variables.push_back({GL_INT, count, sizeof(GLint)}); Size += count * sizeof(GLint);
	return *this;
}

VramBufferLayout& VramBufferLayout::Unsigned(unsigned count)
{
	Variables.push_back({GL_UNSIGNED_INT, count, sizeof(GLuint)}); Size += count * sizeof(GLuint);
	return *this;
}
