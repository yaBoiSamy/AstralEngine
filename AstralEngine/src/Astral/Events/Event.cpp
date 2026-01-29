#include <Common.h>

#include "Event.h"
#include "EventListener.h"

namespace Astral {
    bool WindowCloseEvent::Dispatch(EventListener& l) const { return DispatchImpl(l); }
    bool WindowResizeEvent::Dispatch(EventListener& l) const { return DispatchImpl(l); }
    bool WindowFocusEvent::Dispatch(EventListener& l) const { return DispatchImpl(l); }
    bool WindowLostFocusEvent::Dispatch(EventListener& l) const { return DispatchImpl(l); }
    bool WindowMovedEvent::Dispatch(EventListener& l) const { return DispatchImpl(l); }
    bool AppTickEvent::Dispatch(EventListener& l) const { return DispatchImpl(l); }
    bool AppUpdateEvent::Dispatch(EventListener& l) const { return DispatchImpl(l); }
    bool AppRenderEvent::Dispatch(EventListener& l) const { return DispatchImpl(l); }
    bool KeyPressedEvent::Dispatch(EventListener& l) const { return DispatchImpl(l); }
    bool KeyReleasedEvent::Dispatch(EventListener& l) const { return DispatchImpl(l); }
    bool MouseButtonPressedEvent::Dispatch(EventListener& l) const { return DispatchImpl(l); }
    bool MouseButtonReleasedEvent::Dispatch(EventListener& l) const { return DispatchImpl(l); }
    bool MouseMovedEvent::Dispatch(EventListener& l) const { return DispatchImpl(l); }
    bool MouseScrolledEvent::Dispatch(EventListener& l) const { return DispatchImpl(l); }


    Event::operator std::string() const {
        return "Event {}";
    }

    WindowEvent::operator std::string() const {
        return "WindowEvent {}";
    }

    AppEvent::operator std::string() const {
        return "AppEvent {}";
    }

    InputEvent::operator std::string() const {
        return "InputEvent {}";
    }

    WindowCloseEvent::operator std::string() const {
        return "WindowCloseEvent {}";
    }

    WindowResizeEvent::operator std::string() const {
        return std::format("WindowResizeEvent {{ width = {0}, height = {1} }}", width, height);
    }

    WindowFocusEvent::operator std::string() const {
        return "WindowFocusEvent";
    }

    WindowLostFocusEvent::operator std::string() const {
        return "WindowLostFocusEvent";
    }

    WindowMovedEvent::operator std::string() const {
        return std::format("WindowMovedEvent {{ x = {0}, y = {1} }}", x, y);
    }

    AppTickEvent::operator std::string() const {
        return "AppTickEvent";
    }

    AppUpdateEvent::operator std::string() const {
        return "AppUpdateEvent";
    }

    AppRenderEvent::operator std::string() const {
        return "AppRenderEvent";
    }

    KeyPressedEvent::operator std::string() const {
        return std::format("KeyPressedEvent {{ keycode = {0}, repeatCount = {1} }}", keycode, repeatCount);
    }

    KeyReleasedEvent::operator std::string() const {
        return std::format("KeyReleasedEvent {{ keycode = {0} }}", keycode);
    }

    MouseButtonPressedEvent::operator std::string() const {
        return std::format("MouseButtonPressedEvent {{ button = {0}, x = {1}, y = {2} }}", button, x, y);
    }

    MouseButtonReleasedEvent::operator std::string() const {
        return std::format("MouseButtonReleasedEvent {{ button = {0}, x = {1}, y = {2} }}", button, x, y);
    }

    MouseMovedEvent::operator std::string() const {
        return std::format("MouseMovedEvent {{ x = {0}, y = {1} }}", x, y);
    }

    MouseScrolledEvent::operator std::string() const {
        return std::format("MouseScrolledEvent {{ x = {0}, y = {1} }}", xOffset, yOffset);
    }
}
