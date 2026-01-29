#include <Common.h>
#include "EventListener.h"
#include "Astral/Events/Event.h"

namespace Astral
{
	bool EventListener::Accept(const Event& event) { return OnEvent(event); }
	bool EventListener::Accept(const WindowEvent& event) { Accept(static_cast<const Event&>(event)); return OnWindowEvent(event); }
	bool EventListener::Accept(const AppEvent& event) { Accept(static_cast<const Event&>(event)); return OnAppEvent(event); }
	bool EventListener::Accept(const InputEvent& event) { Accept(static_cast<const Event&>(event)); return OnInputEvent(event); }
	bool EventListener::Accept(const WindowCloseEvent& event) { Accept(static_cast<const WindowEvent&>(event)); return OnWindowCloseEvent(event); }
	bool EventListener::Accept(const WindowResizeEvent& event) { Accept(static_cast<const WindowEvent&>(event)); return OnWindowResizeEvent(event); }
	bool EventListener::Accept(const WindowFocusEvent& event) { Accept(static_cast<const WindowEvent&>(event)); return OnWindowFocusEvent(event); }
	bool EventListener::Accept(const WindowLostFocusEvent& event) { Accept(static_cast<const WindowEvent&>(event)); return OnWindowLostFocusEvent(event); }
	bool EventListener::Accept(const WindowMovedEvent& event) { Accept(static_cast<const WindowEvent&>(event)); return OnWindowMovedEvent(event); }
	bool EventListener::Accept(const AppTickEvent& event) { Accept(static_cast<const AppEvent&>(event)); return OnAppTickEvent(event); }
	bool EventListener::Accept(const AppUpdateEvent& event) { Accept(static_cast<const AppEvent&>(event)); return OnAppUpdateEvent(event); }
	bool EventListener::Accept(const AppRenderEvent& event) { Accept(static_cast<const AppEvent&>(event)); return OnAppRenderEvent(event); }
	bool EventListener::Accept(const KeyPressedEvent& event) { Accept(static_cast<const InputEvent&>(event)); return OnKeyPressedEvent(event); }
	bool EventListener::Accept(const KeyReleasedEvent& event) { Accept(static_cast<const InputEvent&>(event)); return OnKeyReleasedEvent(event); }
	bool EventListener::Accept(const MouseButtonPressedEvent& event) { Accept(static_cast<const InputEvent&>(event)); return OnMouseButtonPressedEvent(event); }
	bool EventListener::Accept(const MouseButtonReleasedEvent& event) { Accept(static_cast<const InputEvent&>(event)); return OnMouseButtonReleasedEvent(event); }
	bool EventListener::Accept(const MouseMovedEvent& event) { Accept(static_cast<const InputEvent&>(event)); return OnMouseMovedEvent(event); }
	bool EventListener::Accept(const MouseScrolledEvent& event) { Accept(static_cast<const InputEvent&>(event)); return OnMouseScrolledEvent(event); }
}
