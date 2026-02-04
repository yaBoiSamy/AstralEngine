#pragma once

#include "Common.h"

#include "Astral/Events/Event.h"
#include "Astral/Core.h"
#include "Astral/Window/FrameContext.h"

struct GLFWwindow;

namespace Astral {

	using EventCallbackFn = std::function<void(Event const&)>;

	class ASTRAL_API Window {
	public:
		struct State {
			State(FrameContext::WindowSnapshot const& snapshot)	: 
				title(snapshot.title), 
				x(snapshot.x),
				y(snapshot.y),
				width(snapshot.width), 
				height(snapshot.height), 
				focused(snapshot.focused),
				vSync(snapshot.vSync) {}

			std::string title;
			uint32_t x, y;
			uint32_t width, height;
			bool focused;
			bool vSync;
		};

		explicit Window(GLFWwindow* handle, FrameContext::WindowSnapshot state, std::function<void()> imguiSetup);

		FrameContext GetFrameContext() const;
		FrameContext::WindowSnapshot GetWindowState() const;
		FrameContext::InputSnapshot GetInputState() const;

		void SetCallback(std::function<void(const Event&)> callback);
		void SetVSync(bool vSync);

		double GetDeltaTime() const;    
		std::pair<uint32_t, uint32_t> GetFramebufferSize() const;

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
