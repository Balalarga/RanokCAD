#pragma once

#include <SDL.h>
#include <glm/vec2.hpp>
#include <string>

#include "../Core/RenderTarget.h"
#include "InputManager.h"


class Window: public RenderTarget
{
	friend class InputManager;

public:
	struct Params
	{
		std::string Title = {"Window"};
		Uint32 Subsystems = SDL_INIT_EVERYTHING;
		SDL_Point Size = {1280, 720};
		SDL_Point Pos = {SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED};
		bool IsFullScreen = false;
		size_t Flags = sWindowDefaultFlags;

		const char* imguiGlVersion = "#version 330";
	};


	static size_t sWindowDefaultFlags;


	Window(Params params = {});
	virtual ~Window();

	virtual void Open();
	virtual void Close();

	void Present() override;
	void Bind() override;
	void Release() override;

	virtual void Resize(unsigned x, unsigned y);
	virtual glm::uvec2 GetSize();
	uint32_t GetWindowId() const;


	const Params& GetParams() const
	{
		return _params;
	}

	bool IsOpen() const
	{
		return _isOpen;
	}


protected:
	// InputManager funcs
	virtual void OnWindowResize(const glm::ivec2& newSize);

	Params _params;

	SDL_Window* _sdlWindow{};
	SDL_GLContext _openglContext{};

	bool _isOpen = false;
};
