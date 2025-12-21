#pragma once

#include <Common.h>

namespace Astral {

    struct Event {
        void Dispatch() const;
        virtual operator std::string() const;
    };

    struct WindowEvent : Event {
        void Dispatch() const;
        virtual operator std::string() const;
    };

    struct AppEvent : Event {
        void Dispatch() const;
        virtual operator std::string() const;
    };

    struct InputEvent : Event {
        void Dispatch() const;
        virtual operator std::string() const;
    };

    struct WindowCloseEvent : WindowEvent {
        void Dispatch() const;
        operator std::string() const override;
    };

    struct WindowResizeEvent : WindowEvent {
        const uint32_t width, height;
        WindowResizeEvent(uint32_t width, uint32_t height) : width(width), height(height) {}

        void Dispatch() const;
        operator std::string() const override;
    };

    struct WindowFocusEvent : WindowEvent {
        void Dispatch() const;
        operator std::string() const override;
    };

    struct WindowLostFocusEvent : WindowEvent {
        void Dispatch() const;
        operator std::string() const override;
    };

    struct WindowMovedEvent : WindowEvent {
        const uint32_t x, y;
        WindowMovedEvent(uint32_t x, uint32_t y) : x(x), y(y) {}

        void Dispatch() const;
        operator std::string() const override;
    };

    struct AppTickEvent : AppEvent {
        void Dispatch() const;
        operator std::string() const override;
    };

    struct AppUpdateEvent : AppEvent {
        void Dispatch() const;
        operator std::string() const override;
    };

    struct AppRenderEvent : AppEvent {
        void Dispatch() const;
        operator std::string() const override;
    };

    struct KeyPressedEvent : InputEvent {
        const uint32_t keycode, repeatCount;
        KeyPressedEvent(uint32_t keycode, uint32_t repeatCount) : keycode(keycode), repeatCount(repeatCount) {}

        void Dispatch() const;
        operator std::string() const override;
    };

    struct KeyReleasedEvent : InputEvent {
        const uint32_t keycode;
        KeyReleasedEvent(uint32_t keycode) : keycode(keycode) {}

        void Dispatch() const;
        operator std::string() const override;
    };

    struct MouseButtonPressedEvent : InputEvent {
        const double button, x, y;
        MouseButtonPressedEvent(uint32_t button, double x, double y) : button(button), x(x), y(y) {}

        void Dispatch() const;
        operator std::string() const override;
    };

    struct MouseButtonReleasedEvent : InputEvent {
        const uint32_t button;
        const double x, y;
        MouseButtonReleasedEvent(uint32_t button, double x, double y) : button(button), x(x), y(y) {}

        void Dispatch() const;
        operator std::string() const override;
    };

    struct MouseMovedEvent : InputEvent {
        const double x, y;
        MouseMovedEvent(double x, double y) : x(x), y(y) {}
        
        void Dispatch() const;
        operator std::string() const override;
    };

    struct MouseScrolledEvent : InputEvent {
        const double xOffset, yOffset;
        MouseScrolledEvent(double xOffset, double yOffset) : xOffset(xOffset), yOffset(yOffset) {}

        void Dispatch() const;
        operator std::string() const override;
    };

    //std::string ToString(Event& event);
}
