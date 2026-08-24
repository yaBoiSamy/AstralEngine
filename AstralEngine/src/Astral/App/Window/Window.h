#pragma once

#include <Common.h>

#include "Astral/App/Events/EventHandlers/EventHandlers.h"
#include "Astral/App/FrameContext.h"

struct GLFWwindow;

namespace Astral::App {

	class Window : public EventBroadcaster {
	public:
		struct State {
			std::string title;
			int32_t x, y;
			uint32_t width, height;
			uint32_t frame_width, frame_height;
			bool focused;
			bool vsync;
			double deltatime;
		};

		explicit Window(GLFWwindow* handle, State state, std::function<void()> imguiSetup);

		FrameContext GetFrameContext() const;
		FrameContext::WindowSnapshot GetWindowState() const;
		FrameContext::InputSnapshot GetInputState() const;

		void SetVSync(bool vsync);

		void PumpEvents();

		void MakeContextCurrent() const;
		void SwapBuffers();

		Window(Window&&) noexcept = default; 
		Window& operator=(Window&&) noexcept = default; 

		// Copying forbidden to avoid glfw user pointer issues
		Window(const Window&) = delete; 
		Window& operator=(const Window&) = delete;

	private:
		struct GLFWDeleter {
			void operator()(GLFWwindow* w) const noexcept;
		};

		Box<State> state;
		Box<GLFWwindow, GLFWDeleter> handle;
	};
}
