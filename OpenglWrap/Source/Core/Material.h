#pragma once
#include <array>
#include <map>
#include <memory>

#include "Shader.h"
#include "UniformValue.h"

class Material: public VramHandle
{
public:
	Material() = default;
	Material(ShaderKit kit, bool bAutoInit = true);
	Material(ShaderSourceKit kit, bool bAutoInit = true);
	virtual ~Material();

	virtual void SetupUniforms();

	void SetShader(std::shared_ptr<Shader> shader);
	std::shared_ptr<Shader> GetShader(Shader::Type type);

	void SetUniform(const std::string& name, const UniformValue& value);

	bool Init() override;

	void Bind();
	static void Release();


protected:
	int GetUniformLocation(const std::string& name);

	int AllocateVram() override;
	void DeallocateVram() override;


private:
	std::array<std::shared_ptr<Shader>, static_cast<size_t>(Shader::Type::Count)> _shaders;
	std::map<std::string, int> _uniforms;
};
