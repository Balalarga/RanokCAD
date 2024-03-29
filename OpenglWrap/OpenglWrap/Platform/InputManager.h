﻿#pragma once

#include <functional>
#include "SDL.h"
#include "glm/vec2.hpp"
#include <vector>


enum class KeyState
{
	Pressed, Released, Repeated
};


enum class MouseKey: uint8_t
{
	Left = 0,
	Middle,
	Right,
	X1,
	X2
};


struct MouseState
{
	glm::vec2 pos;
	glm::vec2 moved;
	KeyState keys[5];
};


class InputManager
{
	friend class Window;
public:
	using KeyCallback = std::function<void(Window&, const KeyState&)>;
	using MouseMoveCallback = std::function<void(Window&, const MouseState&)>;
	using MouseKeyCallback = std::function<void(Window&, const MouseKey&, const KeyState&, glm::ivec2, int)>;

	InputManager(Window& window);

	void Add(SDL_Scancode code, const KeyCallback& callback);
	bool Remove(SDL_Scancode code, const KeyCallback& callback);

	void AddOnMouseMove(const MouseMoveCallback& callback);
	void AddOnMouseKey(MouseKey key, const MouseKeyCallback& callback);

	void HandleEvent();


protected:
	void OnStateChange(SDL_Scancode code, KeyState state) const;
	void OnMouseKey(const MouseKey&, const KeyState&, glm::ivec2, int) const;

private:
	Window& _window;
	std::vector<KeyCallback> _keyCallbacks[SDL_NUM_SCANCODES];
	std::vector<MouseMoveCallback> _onMouseMoveCallbacks;
	std::vector<MouseKeyCallback> _mouseKeyCallbacks[5];
};
