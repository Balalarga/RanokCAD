#pragma once

#include <memory>
#include <string>

#include "VramHandle.h"


class Shader;


struct ShaderKit
{
	std::shared_ptr<Shader> vertexShader;
	std::shared_ptr<Shader> fragmentShader;
	std::shared_ptr<Shader> geometryShader;
};

struct ShaderSourceKit
{
	std::string_view vertexShader = {};
	std::string_view fragmentShader = {};
	std::string_view geometryShader = {};
};


class Shader: public VramHandle
{
public:
	enum class Type: uint8_t
	{
		Vertex = 0, Fragment, Geometry, Count
	};
	static int GetGlType(Type type);

	Shader(Type type, std::string_view code = "");
	virtual ~Shader();

	const std::string& GetSourceCode() const { return _code; }
	Type GetType() const { return _type; }

	bool Init() override;
	bool Init(const std::string& code);


protected:
	int AllocateVram() override;
	void DeallocateVram() override;

	bool HasError() const;


private:
	const Type _type;
	std::string _code;
};
