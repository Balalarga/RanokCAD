#include "RenderApi.h"

#include "RenderTarget.h"

RenderApi::RenderApi() : _defaultClearColor(0.1f, 0.1f, 0.1f, 1.0f)
{
}

void RenderApi::PushTarget(RenderTarget* target)
{
	auto& api = Get();
	api._targetsStack.push_back(target);
	target->Bind();
}

void RenderApi::PushTarget(RenderTarget& target)
{
	PushTarget(&target);
}

RenderTarget* RenderApi::PopTarget()
{
	auto& api = Get();
	if (api._targetsStack.empty())
		return nullptr;

	RenderTarget* last = api._targetsStack.back();
	last->Release();
	api._targetsStack.pop_back();
	return last;
}

void RenderApi::Clear(int buffers)
{
	auto& api = Get();
	glClearColor(
		api._defaultClearColor.x, api._defaultClearColor.y, api._defaultClearColor.z, api._defaultClearColor.w);
	glClear(buffers);
}

void RenderApi::ClearWithColor(const glm::vec4& color, int buffers)
{
	auto& api = Get();
	glClearColor(color.x, color.y, color.z, color.w);
	glClear(buffers);
}

void RenderApi::Present()
{
	auto& api = Get();
	if (!api._targetsStack.empty())
		api._targetsStack.back()->Present();
}

void RenderApi::SetDefaultClearColor(const glm::vec4& color)
{
	auto& api = Get();
	api._defaultClearColor = color;
}

RenderApi& RenderApi::Get()
{
	static RenderApi api;
	return api;
}
