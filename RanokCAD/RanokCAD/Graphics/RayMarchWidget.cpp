#include "RayMarchWidget.h"

#include <ImGui/imgui_internal.h>
#include <Inja/inja.hpp>
#include <iostream>

#include "BoundingBox.h"
#include "ImGui/imgui.h"
#include "OpenglWrap/Camera.h"
#include "OpenglWrap/Core/Material.h"
#include "OpenglWrap/Core/RenderApi.h"
#include "OpenglWrap/Core/SceneObject.h"


static std::string backVsh = R"(
#version 420

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 uv;

layout(location = 0) out vec2 vUv;

void main()
{
    gl_Position = vec4(position, 0.0, 1.0);
	vUv = uv;
}
)";

static std::string backFsh = R"(
#version 420

layout(location = 0) in vec2 vUv;
layout(location = 0) out vec4 oColor;


void main()
{
    oColor = vec4(0.1, 0.1, 0.1, 1.0);
}
)";

struct RM_Vertex
{
	glm::vec2 pos, uv;
};

static std::vector<RM_Vertex> backObjData{
	{{-1, -1}, {0, 0}},
	{{-1, 1}, {0, 1}},
	{{1, 1}, {1, 1}},
	{{1, 1}, {1, 1}},
	{{1, -1}, {1, 0}},
	{{-1, -1}, {0, 0}},
};

static std::string shapeVsh = R"(
#version 420

layout(location = 0) in vec3 position;

layout(location = 0) out float vDepth;

uniform mat4 uMVP = mat4(1);
uniform vec3 uCameraPos;
uniform float uCameraFov;
uniform float uCameraNear;
uniform float uCameraFar;


void main()
{
    gl_Position = uMVP * vec4(position, 1.0);

	float invNear = 1/uCameraNear;
	vDepth = (1/(position.z - uCameraPos.z) - invNear) / (1/uCameraFar - invNear);
}
)";

static std::string shapeFsh = R"(
#version 420

layout(location = 0) in float vDepth;

layout(location = 0) out vec4 oColor;

void main()
{
	oColor = vec4(1, 1, 1, vDepth);
}
)";

static std::vector<glm::vec3> shapeObjData{
	{-1, -1, 0},
	{-1, 1, 0},
	{1, 1, 0},
	{1, -1, 2},
};

RayMarchWidget::RayMarchWidget(glm::ivec2 size)
	: FboWidget(size)
	, _camera(60.f, size.x / size.y, 0.1f, 100.f)
	, _material(std::make_shared<Material>(ShaderSourceKit{.vertexShader = backVsh}))
	, _obj(std::make_shared<SceneObject>(
		  LaidVramBuffer(RawPtrData(backObjData), VramBufferLayout().Float(2).Float(2)), _material))
	, _materialFwd(std::make_shared<Material>(ShaderSourceKit{.vertexShader = shapeVsh, .fragmentShader = shapeFsh}))
	, _objFwd(std::make_shared<BoundingBox>(glm::vec3(3), _materialFwd))
{
	_camera.Move({0, 0, -4});
	AddRenderingTexture(GL_COLOR_ATTACHMENT0, size, 4);

	_material->SetShader(std::make_shared<Shader>(Shader::Type::Fragment, backFsh));
	if (!_material->Construct() || !_materialFwd->Construct())
	{
		std::cout << "_material error\n";
	}

	if (!_obj->Construct() || !_objFwd->Construct())
	{
		std::cout << "_obj error\n";
	}
}

RayMarchWidget::~RayMarchWidget()
{
	RayMarchWidget::Destroy();
}

void RayMarchWidget::SetObjects(const std::vector<Assembly>& assemblies)
{
	inja::Environment env;
	nlohmann::json json;
	for (const Assembly& assembly : assemblies)
		json["Assemblies"].push_back(assembly.GenerateJson());

	auto path = std::filesystem::current_path();
	path /= "Assets/Templates/RayMarch.glsl.templ";
	UpdateCode(env.render_file(path.string(), json));
	SetUniforms(assemblies);
}

void RayMarchWidget::SetUniforms(const std::vector<Assembly>& assemblies) const
{
	_material->Bind();

	for (const Assembly& assembly : assemblies)
	{
		_material->SetUniform(std::format("{}Data.location", assembly.GetName()), assembly.GetLocation());
		_material->SetUniform(std::format("{}Data.color", assembly.GetName()), assembly.GetColor());
		
		assembly.IterateParts([&](const AssemblyPart& part)
		{
			_material->SetUniform(
				std::format("{}_{}Data.location", assembly.GetName(), part.model.GetName()), part.model.GetLocation());
			_material->SetUniform(
				std::format("{}_{}Data.color", assembly.GetName(), part.model.GetName()), part.model.GetColor());
		});
	}

	_material->Release();
}

void RayMarchWidget::UpdateCode(const std::string& fragmentCode)
{
	_material->SetShader(std::make_shared<Shader>(Shader::Type::Fragment, fragmentCode));
	if (!_material->Construct(true))
	{
		std::cout << fragmentCode << std::endl;
	}
}

void RayMarchWidget::Render()
{
	// RenderApi::PushTarget(this);
	// RenderApi::ClearWithColor({0.05, 0.05, 0.2, 1.0});
	// _materialFwd->Bind();
	// _materialFwd->SetUniform("uMVP", _camera.GetUpdatedMatrix());
	// _materialFwd->SetUniform("uCameraPos", _camera.GetLocation());
	// _materialFwd->SetUniform("uCameraFov", _camera.GetFov());
	// _materialFwd->SetUniform("uCameraNear", _camera.GetNear());
	// _materialFwd->SetUniform("uCameraFar", _camera.GetFar());
	// _objFwd->Render();
	// RenderApi::PopTarget();

	RenderApi::PushTarget(this);
	_material->Bind();
	if (const auto texture = GetTexture(GL_COLOR_ATTACHMENT0))
		texture->Bind();
	_material->SetUniform("uResolution", GetSize());
	_material->SetUniform("uCameraPos", _camera.GetLocation());
	_material->SetUniform("uCameraDir", _camera.GetRotation());
	_material->SetUniform("uCameraFov", _camera.GetFov());
	_material->SetUniform("uCameraNear", _camera.GetNear());
	_material->SetUniform("uCameraFar", _camera.GetFar());
	_material->SetUniform("uCameraFar", _camera.GetFar());
	_obj->Render();
	RenderApi::PopTarget();
}

void RayMarchWidget::DrawGui()
{
	Render();
	if (ImGui::GetCurrentWindowRead())
		FboWidget::DrawGui();
}
