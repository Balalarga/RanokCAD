#include "Window.h"

#include <GL/glew.h>
#include <imgui.h>
#include <utility>

#include "../Core/RenderApi.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl2.h"

size_t Window::sWindowDefaultFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_HIDDEN;

Window::Window(Params params) : _params(std::move(params))
{
	assert(SDL_Init(_params.Subsystems) == 0);
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	_sdlWindow = SDL_CreateWindow(
		_params.Title.c_str(), _params.Pos.x, _params.Pos.y, _params.Size.x, _params.Size.y, _params.Flags);
	assert(_sdlWindow);

	_openglContext = SDL_GL_CreateContext(_sdlWindow);
	assert(_openglContext);

	glewExperimental = GL_TRUE;
	assert(glewInit() == GLEW_OK);

	ImGui_ImplSDL2_InitForOpenGL(_sdlWindow, _openglContext);
	ImGui_ImplOpenGL3_Init(_params.imguiGlVersion);

	SDL_GL_MakeCurrent(_sdlWindow, _openglContext);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	RenderApi::PushTarget(this);
}

Window::~Window()
{
	RenderApi::PopTarget();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_GL_DeleteContext(_openglContext);
	SDL_DestroyWindow(_sdlWindow);
	SDL_Quit();
}

void Window::Close()
{
	if (!_isOpen)
		return;

	SDL_HideWindow(_sdlWindow);
	_isOpen = false;
}

void Window::Open()
{
	if (_isOpen)
		return;

	_isOpen = true;
	SDL_ShowWindow(_sdlWindow);
}

void Window::Present()
{
	SDL_GL_SwapWindow(_sdlWindow);
}

void Window::Bind()
{
}

void Window::Release()
{
}

void Window::Resize(unsigned x, unsigned y)
{
	SDL_SetWindowSize(_sdlWindow, static_cast<int>(x), static_cast<int>(y));
}

glm::uvec2 Window::GetSize()
{
	glm::ivec2 size;
	SDL_GetWindowSize(_sdlWindow, &size.x, &size.y);
	return size;
}

uint32_t Window::GetWindowId() const
{
	return SDL_GetWindowID(_sdlWindow);
}

void Window::OnWindowResize(const glm::ivec2& newSize)
{
}
