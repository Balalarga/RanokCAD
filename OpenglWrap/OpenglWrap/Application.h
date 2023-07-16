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

	Application(Params params = {});
	virtual ~Application() = default;

	void Run();

	template<class T, class... TArgs>
	void SetWindow(TArgs&&... args)
	{
		_window = std::make_unique<T>(args...);
	}

	Window* GetWindow() const
	{
		return _window.get();
	}
	template<class T>
	T* GetWindow() const
	{
		return _window.get();
	}

	template<class T, class... TArgs>
	void SetInputManager(TArgs&&... args)
	{
		_inputManager = std::make_unique<T>(args...);
	}
	InputManager* GetInputManager()
	{
		return _inputManager.get();
	}
	template<class T>
	T* GetInputManager()
	{
		return dynamic_cast<T*>(_inputManager.get());
	}

	virtual void Render();
	virtual void RenderImGui();
	virtual void Update(float delta);

	void SetOnRender(const std::function<void()>& func);
	void SetOnImGuiRender(const std::function<void()>& func);
	void SetOnUpdate(const std::function<void(float)>& func);


private:
	Params _params;
	std::unique_ptr<Window> _window;
	std::unique_ptr<InputManager> _inputManager;

	std::function<void()> _onRender;
	std::function<void()> _onImGuiRender;
	std::function<void(float)> _onUpdate;
};
