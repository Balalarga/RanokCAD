#include "RayMarchWidget.h"

#include "../../RanokLang/Source/Parser.h"
#include "Core/Material.h"
#include "Core/RenderApi.h"
#include "Core/SceneObject.h"
#include "Generators/MultiObjectShaderGenerator.h"
#include "Lexer.h"

std::string vShader = R"(
#version 330
layout(location = 0) in vec2 position;
void main()
{
    gl_Position = vec4(position, 0.0, 1.0);
}
)";

std::vector<glm::vec2> screenRect{
	{-1, -1},
	{-1, 1},
	{1, 1},
	{1, 1},
	{1, -1},
	{-1, -1},
};

RayMarchWidget::RayMarchWidget(glm::ivec2 size, int channels) :
	FboWidget(size, channels), _material(std::make_shared<Material>(ShaderSourceKit{.vertexShader = vShader})),
	_obj(std::make_shared<SceneObject>(
		LaidVramBuffer(RawPtrData(screenRect), VramBufferLayout().Float(2)), _material, false))
{
	MultiObjectShaderGenerator generator;
	constexpr auto code1 = R"(
def main(s[3])
{
	r = 1;
	return r^2 - (s[0]-r)^2.0 - s[1]^2.0 - s[2]^2.0;
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
	return (r - s[0]^2.0 - s[1]^2.0 - s[2]^2.0)|(r - s[0]^2.0 - s[1]^2.0 - s[2]^2.0);
}
)";
	nlohmann::json objects;
	objects["Objects"] = {};
	Lexer lexer1(code1);
	Lexer lexer2(code2);
	Parser parser;
	ActionTree tree1 = parser.Parse(lexer1);
	if (std::optional<std::string> res = generator.Generate(tree1))
		objects["Objects"].push_back(generator.FlushJson());

	ActionTree tree2 = parser.Parse(lexer2);
	if (std::optional<std::string> res = generator.Generate(tree2))
		objects["Objects"].push_back(generator.FlushJson());

	auto path = std::filesystem::current_path();
	path /= "Templates/RayMarch.glsl.templ";

	inja::Environment env;
	_material->SetShader(std::make_shared<Shader>(Shader::Type::Fragment, env.render_file(path.string(), objects)));

	if (!_material->Init())
	{
		std::cout << "error\n";
	}
	std::cout << env.render_file(path.string(), objects) << std::endl;
	_obj->Init();
}

void RayMarchWidget::UpdateCode(const std::string& fragmentCode)
{
	_material->SetShader(std::make_shared<Shader>(Shader::Type::Fragment, fragmentCode));
}

void RayMarchWidget::Render()
{
	RenderApi::PushTarget(this);
	// RenderApi::ClearColor({0.05, 0.05, 0.05, 1.0});
	RenderApi::Clear();
	_material->Bind();
	_obj->Render();
	RenderApi::PopTarget();
}

void RayMarchWidget::DrawGui()
{
	Render();
	FboWidget::DrawGui();
}