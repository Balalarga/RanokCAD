#include "RayMarchWidget.h"

#include "BoundingBox.h"
#include "ImGui/imgui.h"
#include "OpenglWrap/Camera.h"
#include "OpenglWrap/Core/Material.h"
#include "OpenglWrap/Core/RenderApi.h"
#include "OpenglWrap/Core/SceneObject.h"
#include "RanokLang/Generators/MultiObjectShaderGenerator.h"
#include "RanokLang/Lexer.h"
#include "RanokLang/Parser.h"

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

uniform vec2 uResolution;

uniform sampler2D tForwardRendering;

void main()
{
    vec4 fwdColor = texture(tForwardRendering, vUv);
	vec2 uv = gl_FragCoord.xy / uResolution.xy;
    //fwdColor = texture(tForwardRendering, uv);
    oColor = vec4(fwdColor.xyz, 1.0);
    //oColor = vec4(1.0, 0.5, 0.5, 1.0);
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

RayMarchWidget::RayMarchWidget(glm::ivec2 size) :
	FboWidget(size),
	_camera(60.f, size.x / size.y, 0.01f, 100.f),
	_material(std::make_shared<Material>(ShaderSourceKit{.vertexShader = backVsh})),
	_obj(std::make_shared<SceneObject>(LaidVramBuffer(RawPtrData(backObjData), VramBufferLayout().Float(2).Float(2)),
									   _material)),
	_materialFwd(std::make_shared<Material>(ShaderSourceKit{.vertexShader = shapeVsh, .fragmentShader = shapeFsh})),
	_objFwd(std::make_shared<BoundingBox>(glm::vec3(3), _materialFwd))
{
	_camera.Move({0, 0, -4});
	AddRenderingTexture(GL_COLOR_ATTACHMENT0, size, 4);

	MultiObjectShaderGenerator generator;
	constexpr auto code1 = R"(
def main(s[3])
{
	r = 1;
	return r^2 - (s[0]-3)^2.0 - s[1]^2.0 - (s[2] + 3)^2.0;
}
)";

	constexpr auto code2 = R"(
def s2()
{
	return 1;
}

def main(s[3])
{
	r = s2();
	return r^2 - s[0]^2 - s[1]^2.0 - s[2]^2.0;
}
)";
	nlohmann::json objects;
	objects["Objects"] = {};
	Lexer lexer1(code1);
	Lexer lexer2(code2);
	Parser parser;
	ActionTree tree1 = parser.Parse(lexer1);
	if (std::optional<std::string> res = generator.Generate(tree1))
	{
		generator.SetColor(0.1f, 0.1f, 0.2f);
		objects["Objects"].push_back(generator.FlushJson());
	}

	ActionTree tree2 = parser.Parse(lexer2);
	if (std::optional<std::string> res = generator.Generate(tree2))
	{
		generator.SetColor(0.1f, 0.2f, 0.1f);
		objects["Objects"].push_back(generator.FlushJson());
	}

	auto path = std::filesystem::current_path();
	path /= "Templates/RayMarch.glsl.templ";

	inja::Environment env;
	_material->SetShader(std::make_shared<Shader>(Shader::Type::Fragment, env.render_file(path.string(), objects)));
	// _material->SetShader(std::make_shared<Shader>(Shader::Type::Fragment, backFsh));

	if (!_material->Construct() || !_materialFwd->Construct())
	{
		std::cout << "_material error\n";
		std::cout << env.render_file(path.string(), objects) << std::endl;
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

void RayMarchWidget::UpdateCode(const std::string& fragmentCode)
{
	_material->SetShader(std::make_shared<Shader>(Shader::Type::Fragment, fragmentCode));
}

void RayMarchWidget::Render()
{
	RenderApi::PushTarget(this);
	RenderApi::ClearWithColor({0.05, 0.05, 0.2, 1.0});
	_materialFwd->Bind();
	_materialFwd->SetUniform("uMVP", _camera.GetUpdatedMatrix());
	_materialFwd->SetUniform("uCameraPos", _camera.GetLocation());
	_materialFwd->SetUniform("uCameraFov", _camera.GetFov());
	_materialFwd->SetUniform("uCameraNear", _camera.GetNear());
	_materialFwd->SetUniform("uCameraFar", _camera.GetFar());
	_objFwd->Render();
	RenderApi::PopTarget();

	RenderApi::PushTarget(this);
	_material->Bind();
	if (const auto texture = GetTexture(GL_COLOR_ATTACHMENT0))
		texture->Bind();
	_material->SetUniform("uResolution", GetSize());
	_material->SetUniform("uCameraPos", _camera.GetLocation());
	_material->SetUniform("uCameraFov", _camera.GetFov());
	_material->SetUniform("uCameraNear", _camera.GetNear());
	_material->SetUniform("uCameraFar", _camera.GetFar());
	_obj->Render();
	RenderApi::PopTarget();
}

void RayMarchWidget::DrawGui()
{
	Render();
	FboWidget::DrawGui();
}
