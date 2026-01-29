#pragma once

#include "Common.h"

#include "Astral/Events/Event.h"
#include "Astral/Core.h"

struct GLFWwindow;

namespace Astral {

	using EventCallbackFn = std::function<void(Event const&)>;

	class ASTRAL_API Window {
	public:
		struct State;

		struct StateSnapshot {
			StateSnapshot(std::string const& title, uint32_t width, uint32_t height, bool vSync)
				: title(title), width(width), height(height), vSync(vSync) {
			}

			StateSnapshot(State const& state)
				: title(state.title), width(state.width), height(state.height), vSync(state.vSync) {
			}

			const std::string title;
			const uint32_t width, height;
			const bool vSync;
		};

		struct State {
			State(StateSnapshot const& snapshot)
				: title(snapshot.title), width(snapshot.width), height(snapshot.height), vSync(snapshot.vSync) {
			}

			std::string title;
			uint32_t width, height;
			bool vSync;
		};

		explicit Window(GLFWwindow* handle, StateSnapshot state, std::function<void()> imguiSetup);

		~Window();

		StateSnapshot GetState() const;

		void SetCallback(std::function<void(const Event&)> calback);

		void SetVSync(bool vSync);

		double GetDeltaTime() const;

		void Update();

		Window(Window&&) noexcept = default; 
		Window& operator=(Window&&) noexcept = default; 

		// Copying forbidden to avoid glfw user pointer issues
		Window(const Window&) = delete; 
		Window& operator=(const Window&) = delete;

	private:
		struct GLFWDeleter {
			void operator()(GLFWwindow* w) const noexcept;
		};

		ptr<State> state;
		ptr<GLFWwindow, GLFWDeleter> handle;
		std::function<void(const Event&)> callback;
	};
}
