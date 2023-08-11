#pragma once
#include <memory>
#include "Platform/Window.h"


class Application
{
public:
	struct Params
	{
		int renderRate = 60;
		int updateRate = 30;
		Window::Params windowInitializer{};
	};


	explicit Application(Params params = {});
	virtual ~Application() = default;

	virtual void Render();
	virtual void RenderImGui();
	virtual void Update(float delta);

	void Run();
	void SetOnRenderEvent(const std::function<void()>& func);
	void SetOnImGuiRenderEvent(const std::function<void()>& func);
	void SetOnUpdateEvent(const std::function<void(float)>& func);

	Window* GetWindow() const
	{
		return _window.get();
	}

	InputManager* GetInputManager()
	{
		return _inputManager.get();
	}


private:
	Params _params;
	std::unique_ptr<Window> _window;
	std::unique_ptr<InputManager> _inputManager;

	std::function<void()> _onRenderEvent;
	std::function<void()> _onImGuiRenderEvent;
	std::function<void(float)> _onUpdateEvent;
};
