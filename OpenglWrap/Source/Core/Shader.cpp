#include "Shader.h"

#include <vector>

#include "GL/glew.h"


Shader::Shader(Type type, std::string_view code):
	_type(type),
	_code(code)
{
}

Shader::~Shader()
{
	Shader::Destroy();
}

bool Shader::Init()
{
	if (*this)
		return true;

	if (_code.empty() || !VramHandle::Init())
		return false;

	const char* rawSource = _code.c_str();
	glShaderSource(GetHandle(), 1, &rawSource, nullptr);
	glCompileShader(GetHandle());

	if (HasError())
		return false;

	return true;
}

bool Shader::Init(const std::string& code)
{
	if (_code.empty())
		return false;

	_code = code;
	return Init();
}

int Shader::AllocateVram()
{
	return glCreateShader(GetGlType(_type));
}

void Shader::DeallocateVram()
{
	glDeleteShader(GetHandle());
}

int Shader::GetGlType(Type type)
{
	switch (type)
	{
		case Type::Vertex:
			return GL_VERTEX_SHADER;
		case Type::Fragment:
			return GL_FRAGMENT_SHADER;
		case Type::Geometry:
			return GL_GEOMETRY_SHADER;
		case Type::Count:
			break;
	}
	return GL_NONE;
}

bool Shader::HasError() const
{
	GLint isCompiled;
	glGetShaderiv(GetHandle(), GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength;
		glGetShaderiv(GetHandle(), GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(GetHandle(), maxLength, &maxLength, errorLog.data());
		// Process log
		return true;
	}
	return false;
}
