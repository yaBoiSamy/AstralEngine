#pragma once
#include <Common.h>

namespace Astral {
    class EventListener;

    struct Event {
        virtual operator std::string() const;
        virtual bool Dispatch(EventListener& l) const = 0;
    };

    struct WindowEvent : Event {
        virtual operator std::string() const;
        virtual bool Dispatch(EventListener& l) const = 0;
    };

    struct AppEvent : Event {
        virtual operator std::string() const;
        virtual bool Dispatch(EventListener& l) const = 0;
    };

    struct InputEvent : Event {
        virtual operator std::string() const;
        virtual bool Dispatch(EventListener& l) const = 0;
    };

    struct WindowCloseEvent : WindowEvent {
        operator std::string() const override;
        virtual bool Dispatch(EventListener& l) const override;
    };

    struct WindowResizeEvent : WindowEvent {
        const uint32_t width, height;
        WindowResizeEvent(uint32_t width, uint32_t height) : width(width), height(height) {}
        operator std::string() const override;
        virtual bool Dispatch(EventListener& l) const override;
    };

    struct WindowFocusEvent : WindowEvent {
        operator std::string() const override;
        virtual bool Dispatch(EventListener& l) const override;
    };

    struct WindowLostFocusEvent : WindowEvent {
        operator std::string() const override;
        virtual bool Dispatch(EventListener& l) const override;
    };

    struct WindowMovedEvent : WindowEvent {
        const uint32_t x, y;
        WindowMovedEvent(uint32_t x, uint32_t y) : x(x), y(y) {}
        operator std::string() const override;
        virtual bool Dispatch(EventListener& l) const override;
    };

    struct AppTickEvent : AppEvent {
        operator std::string() const override;
        virtual bool Dispatch(EventListener& l) const override;
    };

    struct AppUpdateEvent : AppEvent {
        operator std::string() const override;
        virtual bool Dispatch(EventListener& l) const override;
    };

    struct AppRenderEvent : AppEvent {
        operator std::string() const override;
        virtual bool Dispatch(EventListener& l) const override;
    };

    struct KeyPressedEvent : InputEvent {
        const uint32_t keycode, repeatCount;
        KeyPressedEvent(uint32_t keycode, uint32_t repeatCount) : keycode(keycode), repeatCount(repeatCount) {}
        operator std::string() const override;
        virtual bool Dispatch(EventListener& l) const override;
    };

    struct KeyReleasedEvent : InputEvent {
        const uint32_t keycode;
        KeyReleasedEvent(uint32_t keycode) : keycode(keycode) {}
        operator std::string() const override;
        virtual bool Dispatch(EventListener& l) const override;
    };

    struct MouseButtonPressedEvent : InputEvent {
		const uint32_t button;
        const double x, y;
        MouseButtonPressedEvent(uint32_t button, double x, double y) : button(button), x(x), y(y) {}
        operator std::string() const override;
        virtual bool Dispatch(EventListener& l) const override;
    };

    struct MouseButtonReleasedEvent : InputEvent {
        const uint32_t button;
        const double x, y;
        MouseButtonReleasedEvent(uint32_t button, double x, double y) : button(button), x(x), y(y) {}
        operator std::string() const override;
        virtual bool Dispatch(EventListener& l) const override;
    };

    struct MouseMovedEvent : InputEvent {
        const double x, y;
        MouseMovedEvent(double x, double y) : x(x), y(y) {}
        operator std::string() const override;
        virtual bool Dispatch(EventListener& l) const override;
    };

    struct MouseScrolledEvent : InputEvent {
        const double xOffset, yOffset;
        MouseScrolledEvent(double xOffset, double yOffset) : xOffset(xOffset), yOffset(yOffset) {}
        operator std::string() const override;
        virtual bool Dispatch(EventListener& l) const override;
    };


    template<typename T>
    concept EventType = std::is_base_of_v<Event, T>;
}
