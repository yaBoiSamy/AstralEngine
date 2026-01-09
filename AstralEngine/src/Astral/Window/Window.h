#pragma once

#include <Common.h>

#include "Astral/Events/Event.h"
#include "Astral/Core.h"

struct GLFWwindow;

namespace Astral {

	using EventCallbackFn = std::function<void(Event const&)>;

	class Window {
	public:

		struct State {
			std::string title;
			uint32_t width, height;
			bool vSync;
		};

		Window(std::string title = "AstralEngine", uint32_t width = 1920, uint32_t height = 1080);
		explicit Window(State state);

		~Window();

		State GetState() const;
		void SetVSync(bool vSync);

		void Update();

		// Forbid moving to avoid corrupting the glfw pointers
		Window(Window&&) = delete;
		Window& operator=(Window&&) = delete;

	private:
		struct GLFWDeleter {
			void operator()(GLFWwindow* w) const noexcept;
		};
		State state;
		ptr<GLFWwindow, GLFWDeleter> handle;

		void SetGLFWCallbacks();
	};
}
