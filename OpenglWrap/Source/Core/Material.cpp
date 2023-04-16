#include "Material.h"

#include <utility>

#include "GL/glew.h"

Material::Material(ShaderKit kit, bool bAutoInit)
{
	_shaders[static_cast<size_t>(Shader::Type::Vertex)] = std::move(kit.vertexShader);
	_shaders[static_cast<size_t>(Shader::Type::Fragment)] = std::move(kit.fragmentShader);
	_shaders[static_cast<size_t>(Shader::Type::Geometry)] = std::move(kit.geometryShader);

	if (bAutoInit)
		Init();
}

Material::Material(ShaderSourceKit kit, bool bAutoInit)
{
	_shaders[static_cast<size_t>(Shader::Type::Vertex)] = std::make_shared<Shader>(Shader::Type::Vertex, kit.vertexShader);
	_shaders[static_cast<size_t>(Shader::Type::Fragment)] = std::make_shared<Shader>(Shader::Type::Fragment, kit.fragmentShader);
	if (!kit.geometryShader.empty())
		_shaders[static_cast<size_t>(Shader::Type::Fragment)] = std::make_shared<Shader>(Shader::Type::Geometry, kit.geometryShader);

	if (bAutoInit)
		Init();
}

Material::~Material()
{
	Material::Destroy();
}

void Material::SetupUniforms()
{

}

void Material::SetShader(std::shared_ptr<Shader> shader)
{
	assert(shader);
	_shaders[static_cast<size_t>(shader->GetType())] = std::move(shader);
}

std::shared_ptr<Shader> Material::GetShader(Shader::Type type)
{
	return _shaders[static_cast<size_t>(type)];
}

void Material::SetUniform(const std::string& name, const UniformValue& value)
{
	Bind();
	int loc = GetUniformLocation(name);
	if (loc < 0)
		return;

	std::visit([&loc]<typename T0>(T0&& arg)
		{
			using T = std::decay_t<T0>;
			if constexpr (std::is_same_v<T, unsigned>)
				glUniform1ui(loc, arg);
			else if constexpr (std::is_same_v<T, int>)
				glUniform1i(loc, arg);
			else if constexpr (std::is_same_v<T, float>)
				glUniform1f(loc, arg);
			else if constexpr (std::is_same_v<T, glm::vec2>)
				glUniform2fv(loc, 1, &arg.x);
			else if constexpr (std::is_same_v<T, glm::vec3>)
				glUniform3fv(loc, 1, &arg.x);
			else if constexpr (std::is_same_v<T, glm::vec4>)
				glUniform4fv(loc, 1, &arg.x);
			else if constexpr (std::is_same_v<T, glm::mat2>)
				glUniformMatrix2fv(loc, 1, GL_FALSE, &arg[0][0]);
			else if constexpr (std::is_same_v<T, glm::mat3>)
				glUniformMatrix3fv(loc, 1, GL_FALSE, &arg[0][0]);
			else if constexpr (std::is_same_v<T, glm::mat4>)
				glUniformMatrix4fv(loc, 1, GL_FALSE, &arg[0][0]);
		},
		value);
}

bool Material::Init()
{
	if (!VramHandle::Init())
		return false;

	for (const std::shared_ptr<Shader>& shader: _shaders)
	{
		if (shader)
		{
			if (shader->Init())
			{
				glAttachShader(GetHandle(), shader->GetHandle());
			}
			else
			{
				DeallocateVram();
				return false;
			}
		}
	}

	glLinkProgram(GetHandle());
	return true;
}

void Material::Bind()
{
	SetupUniforms();
	glUseProgram(GetHandle());
}

void Material::Release()
{
	glUseProgram(0);
}

int Material::GetUniformLocation(const std::string& name)
{
	const auto it = _uniforms.find(name);
	if (it != _uniforms.end())
		return it->second;

	const int loc = glGetUniformLocation(GetHandle(), name.c_str());
	if (loc >= 0)
		_uniforms[name] = loc;

	return loc;
}

int Material::AllocateVram()
{
	return glCreateProgram();
}

void Material::DeallocateVram()
{
	Release();
	for (std::shared_ptr<Shader>& shader : _shaders)
	{
		if (shader)
			glDetachShader(GetHandle(), shader->GetHandle());
	}
	glDeleteProgram(GetHandle());
}
