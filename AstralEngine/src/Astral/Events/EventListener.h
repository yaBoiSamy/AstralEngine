#pragma once
#include "Astral/Core.h"
#include "Astral/Events/Event.h"


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
		friend struct Event;
		friend struct WindowEvent;
		friend struct AppEvent;
		friend struct InputEvent;
		friend struct WindowCloseEvent;
		friend struct WindowResizeEvent;
		friend struct WindowFocusEvent;
		friend struct WindowLostFocusEvent;
		friend struct WindowMovedEvent;
		friend struct AppTickEvent;
		friend struct MouseScrolledEvent;
		friend struct AppUpdateEvent;
		friend struct AppRenderEvent;
		friend struct KeyPressedEvent;
		friend struct KeyReleasedEvent;
		friend struct MouseButtonPressedEvent;
		friend struct MouseButtonReleasedEvent;
		friend struct MouseMovedEvent;

		bool Accept(const Event& event) { return OnEvent(event); }
		bool Accept(const WindowEvent& event) { Accept(static_cast<const Event&>(event)); return OnWindowEvent(event); }
		bool Accept(const AppEvent& event) { Accept(static_cast<const Event&>(event)); return OnAppEvent(event); }
		bool Accept(const InputEvent& event) { Accept(static_cast<const Event&>(event)); return OnInputEvent(event); }
		bool Accept(const WindowCloseEvent& event) { Accept(static_cast<const WindowEvent&>(event)); return OnWindowCloseEvent(event); }
		bool Accept(const WindowResizeEvent& event) { Accept(static_cast<const WindowEvent&>(event)); return OnWindowResizeEvent(event); }
		bool Accept(const WindowFocusEvent& event) { Accept(static_cast<const WindowEvent&>(event)); return OnWindowFocusEvent(event); }
		bool Accept(const WindowLostFocusEvent& event) { Accept(static_cast<const WindowEvent&>(event)); return OnWindowLostFocusEvent(event); }
		bool Accept(const WindowMovedEvent& event) { Accept(static_cast<const WindowEvent&>(event)); return OnWindowMovedEvent(event); }
		bool Accept(const AppTickEvent& event) { Accept(static_cast<const AppEvent&>(event)); return OnAppTickEvent(event); }
		bool Accept(const AppUpdateEvent& event) { Accept(static_cast<const AppEvent&>(event)); return OnAppUpdateEvent(event); }
		bool Accept(const AppRenderEvent& event) { Accept(static_cast<const AppEvent&>(event)); return OnAppRenderEvent(event); }
		bool Accept(const KeyPressedEvent& event) { Accept(static_cast<const InputEvent&>(event)); return OnKeyPressedEvent(event); }
		bool Accept(const KeyReleasedEvent& event) { Accept(static_cast<const InputEvent&>(event)); return OnKeyReleasedEvent(event); }
		bool Accept(const MouseButtonPressedEvent& event) { Accept(static_cast<const InputEvent&>(event)); return OnMouseButtonPressedEvent(event); }
		bool Accept(const MouseButtonReleasedEvent& event) { Accept(static_cast<const InputEvent&>(event)); return OnMouseButtonReleasedEvent(event); }
		bool Accept(const MouseMovedEvent& event) { Accept(static_cast<const InputEvent&>(event)); return OnMouseMovedEvent(event); }
		bool Accept(const MouseScrolledEvent& event) { Accept(static_cast<const InputEvent&>(event)); return OnMouseScrolledEvent(event); }
	};
}