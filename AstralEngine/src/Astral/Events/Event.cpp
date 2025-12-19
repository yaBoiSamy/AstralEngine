#include <Common.h>

#include "Event.h"
#include "EventDispatcher.h"

namespace Astral {

    void Event::DispatchAsEvent() const{
        EventDispatcher<Event>::Dispatch(*this);
    }

    void WindowEvent::DispatchAsWindowEvent() const{
        EventDispatcher<WindowEvent>::Dispatch(*this);
        DispatchAsEvent();
    }

    void AppEvent::DispatchAsAppEvent() const{
        EventDispatcher<AppEvent>::Dispatch(*this);
        DispatchAsEvent();
    }

    void InputEvent::DispatchAsInputEvent() const{
        EventDispatcher<InputEvent>::Dispatch(*this);
        DispatchAsEvent();
    }

    void WindowCloseEvent::DispatchAsWindowCloseEvent() const{
        EventDispatcher<WindowCloseEvent>::Dispatch(*this);
        DispatchAsWindowEvent();
    }

    void WindowResizeEvent::DispatchAsWindowResizeEvent() const{
        EventDispatcher<WindowResizeEvent>::Dispatch(*this);
        DispatchAsWindowEvent();
    }

    void WindowFocusEvent::DispatchAsWindowFocusEvent() const{
        EventDispatcher<WindowFocusEvent>::Dispatch(*this);
        DispatchAsWindowEvent();
    }

    void WindowLostFocusEvent::DispatchAsWindowLostFocusEvent() const{
        EventDispatcher<WindowLostFocusEvent>::Dispatch(*this);
        DispatchAsWindowEvent();
    }

    void WindowMovedEvent::DispatchAsWindowMovedEvent() const{
        EventDispatcher<WindowMovedEvent>::Dispatch(*this);
        DispatchAsWindowEvent();
    }

    void AppTickEvent::DispatchAsAppTickEvent() const{
        EventDispatcher<AppTickEvent>::Dispatch(*this);
        DispatchAsAppEvent();
    }

    void AppUpdateEvent::DispatchAsAppUpdateEvent() const{
        EventDispatcher<AppUpdateEvent>::Dispatch(*this);
        DispatchAsAppEvent();
    }

    void AppRenderEvent::DispatchAsAppRenderEvent() const {
        EventDispatcher<AppRenderEvent>::Dispatch(*this);
        DispatchAsAppEvent();
    }

    void KeyPressedEvent::DispatchAsKeyPressedEvent() const{
        EventDispatcher<KeyPressedEvent>::Dispatch(*this);
        DispatchAsInputEvent();
    }

    void KeyReleasedEvent::DispatchAsKeyReleasedEvent() const{
        EventDispatcher<KeyReleasedEvent>::Dispatch(*this);
        DispatchAsInputEvent();
    }

    void MouseButtonPressedEvent::DispatchAsMouseButtonPressedEvent() const{
        EventDispatcher<MouseButtonPressedEvent>::Dispatch(*this);
        DispatchAsInputEvent();
    }

    void MouseButtonReleasedEvent::DispatchAsMouseButtonReleasedEvent() const{
        EventDispatcher<MouseButtonReleasedEvent>::Dispatch(*this);
        DispatchAsInputEvent();
    }

    void MouseMovedEvent::DispatchAsMouseMovedEvent() const{
        EventDispatcher<MouseMovedEvent>::Dispatch(*this);
        DispatchAsInputEvent();
    }

    void MouseScrolledEvent::DispatchAsMouseScrolledEvent() const{
        EventDispatcher<MouseScrolledEvent>::Dispatch(*this);
        DispatchAsInputEvent();
    }


    //std::string ToString(const Event& event) {
    //    return std::visit(overloaded{
    //        [](const WindowClose&) {
    //            return std::string("WindowClose");
    //        },

    //        [](const WindowResize& e) {
    //            return std::format("WindowResize({}, {})", e.width, e.height);
    //        },

    //        [](const WindowFocus&) {
    //            return std::string("WindowFocus");
    //        },

    //        [](const WindowLostFocus&) {
    //            return std::string("WindowLostFocus");
    //        },

    //        [](const WindowMoved& e) {
    //            return std::format("WindowMoved({}, {})", e.x, e.y);
    //        },

    //        [](const AppTick&) {
    //            return std::string("AppTick");
    //        },

    //        [](const AppUpdate&) {
    //            return std::string("AppUpdate");
    //        },

    //        [](const AppRender&) {
    //            return std::string("AppRender");
    //        },

    //        [](const KeyPressed& e) {
    //            return std::format("KeyPressed(key={}, repeat={})", e.keycode, e.repeatCount);
    //        },

    //        [](const KeyReleased& e) {
    //            return std::format("KeyReleased(key={})", e.keycode);
    //        },

    //        [](const MouseButtonPressed& e) {
    //            return std::format("MouseButtonPressed(button={}, x={}, y={})", e.button, e.x, e.y);
    //        },

    //        [](const MouseButtonReleased& e) {
    //            return std::format("MouseButtonReleased(button={}, x={}, y={})", e.button, e.x, e.y);
    //        },

    //        [](const MouseMoved& e) {
    //            return std::format("MouseMoved(x={}, y={})", e.x, e.y);
    //        },

    //        [](const MouseScrolled& e) {
    //            return std::format("MouseScrolled(xOffset={}, yOffset={})", e.xOffset, e.yOffset);
    //        }
    //        }, event);
    //}

}
