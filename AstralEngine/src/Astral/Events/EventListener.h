#pragma once
#include "Astral/Core.h"

namespace Astral {
	struct Event;
	struct WindowEvent;
	struct AppEvent;
	struct InputEvent;

	struct WindowCloseEvent;
	struct WindowResizeEvent;
	struct WindowFocusEvent;
	struct WindowLostFocusEvent;
	struct WindowMovedEvent;

	struct AppTickEvent;
	struct AppUpdateEvent;
	struct AppRenderEvent;

	struct KeyPressedEvent;
	struct KeyReleasedEvent;

	struct MouseButtonPressedEvent;
	struct MouseButtonReleasedEvent;
	struct MouseMovedEvent;
	struct MouseScrolledEvent;
}

namespace Astral {
	class ASTRAL_API EventListener {
	public:
		inline virtual bool OnEvent(const Event& event) { return false; }
		inline virtual bool OnWindowEvent(const WindowEvent& event) { return false; }
		inline virtual bool OnAppEvent(const AppEvent& event) { return false; }
		inline virtual bool OnInputEvent(const InputEvent& event) { return false; }
		inline virtual bool OnWindowCloseEvent(const WindowCloseEvent& event) { return false; }
		inline virtual bool OnWindowResizeEvent(const WindowResizeEvent& event) { return false; }
		inline virtual bool OnWindowFocusEvent(const WindowFocusEvent& event) { return false; }
		inline virtual bool OnWindowLostFocusEvent(const WindowLostFocusEvent& event) { return false; }
		inline virtual bool OnWindowMovedEvent(const WindowMovedEvent& event) { return false; }
		inline virtual bool OnAppTickEvent(const AppTickEvent& event) { return false; }
		inline virtual bool OnAppUpdateEvent(const AppUpdateEvent& event) { return false; }
		inline virtual bool OnAppRenderEvent(const AppRenderEvent& event) { return false; }
		inline virtual bool OnKeyPressedEvent(const KeyPressedEvent& event) { return false; }
		inline virtual bool OnKeyReleasedEvent(const KeyReleasedEvent& event) { return false; }
		inline virtual bool OnMouseButtonPressedEvent(const MouseButtonPressedEvent& event) { return false; }
		inline virtual bool OnMouseButtonReleasedEvent(const MouseButtonReleasedEvent& event) { return false; }
		inline virtual bool OnMouseMovedEvent(const MouseMovedEvent& event) { return false; }
		inline virtual bool OnMouseScrolledEvent(const MouseScrolledEvent& event) { return false; }

	private:
		template<typename>
		friend struct EventDispatchKey;

		bool Accept(const Event& event);
		bool Accept(const WindowEvent& event);
		bool Accept(const AppEvent& event);
		bool Accept(const InputEvent& event);
		bool Accept(const WindowCloseEvent& event);
		bool Accept(const WindowResizeEvent& event);
		bool Accept(const WindowFocusEvent& event);
		bool Accept(const WindowLostFocusEvent& event);
		bool Accept(const WindowMovedEvent& event);
		bool Accept(const AppTickEvent& event);
		bool Accept(const AppUpdateEvent& event);
		bool Accept(const AppRenderEvent& event);
		bool Accept(const KeyPressedEvent& event);
		bool Accept(const KeyReleasedEvent& event);
		bool Accept(const MouseButtonPressedEvent& event);
		bool Accept(const MouseButtonReleasedEvent& event);
		bool Accept(const MouseMovedEvent& event);
		bool Accept(const MouseScrolledEvent& event);
	};

	template<typename T>
	concept EventType = std::is_base_of_v<Event, T>;

	template<typename E>
	struct EventDispatchKey {
		static bool Dispatch(const E& e, EventListener& l) requires EventType<E> {
			return l.Accept(e);
		}
	};
}