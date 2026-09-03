#pragma once

#include <Common.h>

#include "Astral/App/Events/EventHandlers/EventHandlers.h"
#include "Astral/App/FrameContext.h"
#include "Astral/App/Application/StartupConfig.h"

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

		explicit Window(const App::StartupConfig& config);

		FrameContext GetFrameContext() const;
		FrameContext::WindowSnapshot GetWindowState() const;
		FrameContext::InputSnapshot GetInputState() const;

		void SetVSync(bool vsync);

		void PumpEvents();

		void MakeContextCurrent() const;
		void SwapBuffers();

		void SetCursorEnabled(bool is_enabled);

		Window(Window&&) noexcept = default; 
		Window& operator=(Window&&) noexcept = default; 

		// Copying forbidden to avoid glfw user pointer issues
		Window(const Window&) = delete; 
		Window& operator=(const Window&) = delete;

	private:
		struct GLFWDeleter {
			void operator()(GLFWwindow* w) const noexcept;
		};

		State state;
		Box<GLFWwindow, GLFWDeleter> handle;
		double last_mouse_x = 0;
		double last_mouse_y = 0;
	};
}
