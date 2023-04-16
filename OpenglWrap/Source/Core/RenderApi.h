#pragma once
#include <GL/glew.h>
#include <glm/vec4.hpp>
#include <vector>

class RenderTarget;

class RenderApi
{
public:
	static void PushTarget(RenderTarget* target);
	static RenderTarget* PopTarget();

	static void Clear(int buffers = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	static void ClearColor(const glm::vec4& color, int buffers = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	static void Present();
	static void SetDefaultClearColor(const glm::vec4& color);

private:
	static RenderApi& Get();

	RenderApi();
	RenderApi(RenderApi&&) = default;
	RenderApi(const RenderApi&) = default;
	RenderApi& operator=(const RenderApi&) = default;

	std::vector<RenderTarget*> _targetsStack;
	glm::vec4 _defaultClearColor;
};
