#pragma once

#include <Common.h>
#include <Astral/Events/Event.h>
#include "Astral/Core.h"

namespace Astral {

	using EventCallbackFn = std::function<void(Event const&)>;

	class Window {
	public:

		struct State {
			std::string title;
			uint32_t width, height;
			bool vSync;
		};

		Window(std::string title, uint32_t width, uint32_t height, bool vSync);
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
		std::unique_ptr<GLFWwindow, GLFWDeleter> handle;
	};
}
