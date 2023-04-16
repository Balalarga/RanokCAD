#include "InputManager.h"

#include "Window.h"
#include "backends/imgui_impl_sdl2.h"

InputManager::InputManager(Window& window) : _window(window)
{
}

void InputManager::Add(SDL_Scancode code, const KeyCallback& callback)
{
	_keyCallbacks[code].push_back(callback);
}

bool InputManager::Remove(SDL_Scancode code, const KeyCallback& callback)
{
	// TODO
	// for (size_t i = 0; i < KeyCallbacks[code].size(); ++i)
	// {
	// if (KeyCallbacks[code][i].target<void(const KeyState&)>() == callback.target<void(const KeyState&)>())
	// {
	// KeyCallbacks[code].erase(KeyCallbacks[code].begin() + i);
	// return true;
	// }
	// }

	return false;
}

void InputManager::AddOnMouseMove(const MouseMoveCallback& callback)
{
	_onMouseMoveCallbacks.push_back(callback);
}

void InputManager::AddOnMouseKey(MouseKey key, const MouseKeyCallback& callback)
{
	_mouseKeyCallbacks[static_cast<int>(key)].push_back(callback);
}

void InputManager::HandleEvent()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		ImGui_ImplSDL2_ProcessEvent(&e);
		switch (e.type)
		{
			case SDL_QUIT:
			{
				_window.Close();
			}
			break;
			case SDL_WINDOWEVENT:
			{
				if (e.window.event == SDL_WINDOWEVENT_CLOSE && _window.GetWindowId() == e.window.windowID)
					_window.Close();
				else if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
					_window.OnWindowResize({e.window.data1, e.window.data2});
			}
			break;
			case SDL_KEYDOWN:
			{
				OnStateChange(e.key.keysym.scancode, e.key.repeat == 0 ? KeyState::Pressed : KeyState::Repeated);
			}
			break;
			case SDL_KEYUP:
			{
				OnStateChange(e.key.keysym.scancode, KeyState::Released);
			}
			break;
			case SDL_MOUSEMOTION:
			{
				KeyState keys[5]{
					e.motion.state & SDL_BUTTON_LMASK ? KeyState::Pressed : KeyState::Released,
					e.motion.state & SDL_BUTTON_MMASK ? KeyState::Pressed : KeyState::Released,
					e.motion.state & SDL_BUTTON_RMASK ? KeyState::Pressed : KeyState::Released,
					e.motion.state & SDL_BUTTON_X1MASK ? KeyState::Pressed : KeyState::Released,
					e.motion.state & SDL_BUTTON_X2MASK ? KeyState::Pressed : KeyState::Released,
				};
				OnMouseMove({e.motion.xrel, e.motion.yrel}, keys);
			}
			break;
			case SDL_MOUSEBUTTONDOWN:
			{
				OnMouseKey(static_cast<MouseKey>(e.button.button - 1),
						   e.button.state == SDL_PRESSED ? KeyState::Pressed : KeyState::Repeated,
						   {e.button.x, e.button.y},
						   e.button.clicks);
			}
			break;
			default: break;
		}
	}
}

void InputManager::OnStateChange(SDL_Scancode code, KeyState state) const
{
	for (const KeyCallback& callback : _keyCallbacks[code])
		callback(_window, state);
}

void InputManager::OnMouseMove(glm::vec2 delta, KeyState keys[5]) const
{
	for (const MouseMoveCallback& callback : _onMouseMoveCallbacks)
		callback(_window, delta, keys);
}

void InputManager::OnMouseKey(const MouseKey& key, const KeyState& state, glm::ivec2 pos, int count) const
{
	for (const MouseKeyCallback& callback : _mouseKeyCallbacks[static_cast<int>(key)])
		callback(_window, key, state, pos, count);
}
