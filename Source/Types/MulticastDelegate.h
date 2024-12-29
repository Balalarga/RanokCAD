#pragma once

#include <functional>
#include <ranges>
#include <spdlog/spdlog.h>
#include <unordered_map>


template<class... TFuncArgs>
class MulticastDelegate {
public:
	constexpr static int InvalidHandle = 0;

	int Bind(std::function<void(TFuncArgs...)>&& Func) const {
		int handle = _handleCounter == -1 ? _handleCounter += 2 : ++_handleCounter;
		while (!_callbacks.try_emplace(_handleCounter, std::move(Func)).second) {
			spdlog::critical("Handle overflow!");
		}
		return handle;
	}

	void Unbind(int handle) const {
		_callbacks.erase(handle);
	}

	void Broadcast(TFuncArgs&&... args) {
		for (const auto& func: _callbacks | std::views::values) {
			func(std::forward<TFuncArgs>(args)...);
		}
	}


private:
	mutable std::unordered_map<int, std::function<void(TFuncArgs...)>> _callbacks;
	mutable int _handleCounter = InvalidHandle;
};