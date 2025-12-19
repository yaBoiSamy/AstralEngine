#pragma once

#include <Common.h>
#include <bitset>

namespace Astral {

    struct Event {
        void DispatchAsEvent() const;
    };

    struct WindowEvent : Event {
        void DispatchAsWindowEvent() const;
    };

    struct AppEvent : Event {
        void DispatchAsAppEvent() const;
    };

    struct InputEvent : Event {
        void DispatchAsInputEvent() const;
    };

    struct WindowCloseEvent : WindowEvent {
        void DispatchAsWindowCloseEvent() const;
    };

    struct WindowResizeEvent : WindowEvent {
        const uint32_t width, height;
        WindowResizeEvent(uint32_t width, uint32_t height) : width(width), height(height) {}

        void DispatchAsWindowResizeEvent() const;
    };

    struct WindowFocusEvent : WindowEvent {
        void DispatchAsWindowFocusEvent() const;
    };

    struct WindowLostFocusEvent : WindowEvent {
        void DispatchAsWindowLostFocusEvent() const;
    };

    struct WindowMovedEvent : WindowEvent {
        const uint32_t x, y;
        WindowMovedEvent(uint32_t x, uint32_t y) : x(x), y(y) {}

        void DispatchAsWindowMovedEvent() const;
    };

    struct AppTickEvent : AppEvent {
        void DispatchAsAppTickEvent() const;
    };

    struct AppUpdateEvent : AppEvent {
        void DispatchAsAppUpdateEvent() const;
    };

    struct AppRenderEvent : AppEvent {
        void DispatchAsAppRenderEvent() const;
    };

    struct KeyPressedEvent : InputEvent {
        const uint32_t keycode, repeatCount;
        KeyPressedEvent(uint32_t keycode, uint32_t repeatCount) : keycode(keycode), repeatCount(repeatCount) {}

        void DispatchAsKeyPressedEvent() const;
    };

    struct KeyReleasedEvent : InputEvent {
        const uint32_t keycode;
        KeyReleasedEvent(uint32_t keycode) : keycode(keycode) {}

        void DispatchAsKeyReleasedEvent() const;
    };

    struct MouseButtonPressedEvent : InputEvent {
        const uint32_t button, x, y;
        MouseButtonPressedEvent(uint32_t button, uint32_t x, uint32_t y) : button(button), x(x), y(y) {}

        void DispatchAsMouseButtonPressedEvent() const;
    };

    struct MouseButtonReleasedEvent : InputEvent {
        const uint32_t button, x, y;
        MouseButtonReleasedEvent(uint32_t button, uint32_t x, uint32_t y) : button(button), x(x), y(y) {}

        void DispatchAsMouseButtonReleasedEvent() const;
    };

    struct MouseMovedEvent : InputEvent {
        const float x, y;
        MouseMovedEvent(float x, float y) : x(x), y(y) {}
        
        void DispatchAsMouseMovedEvent() const;
    };

    struct MouseScrolledEvent : InputEvent {
        const float xOffset, yOffset;
        MouseScrolledEvent(float xOffset, float yOffset) : xOffset(xOffset), yOffset(yOffset) {}

        void DispatchAsMouseScrolledEvent() const;
    };

    //std::string ToString(Event& event);
}
