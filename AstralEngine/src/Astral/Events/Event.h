#pragma once
#include <Common.h>
#include "Astral/Core.h" 

namespace Astral {
    class EventListener;

    struct ASTRAL_API Event {
        virtual operator std::string() const;
        virtual bool Dispatch(EventListener& l) const = 0;
    };

    struct ASTRAL_API WindowEvent : Event {
        virtual operator std::string() const;
        virtual bool Dispatch(EventListener& l) const = 0;
    };

    struct ASTRAL_API AppEvent : Event {
        virtual operator std::string() const;
        virtual bool Dispatch(EventListener& l) const = 0;
    };

    struct ASTRAL_API InputEvent : Event {
        virtual operator std::string() const;
        virtual bool Dispatch(EventListener& l) const = 0;
    };

    struct ASTRAL_API WindowCloseEvent : WindowEvent {
        operator std::string() const override;
        virtual bool Dispatch(EventListener& l) const override;
    };

    struct ASTRAL_API WindowResizeEvent : WindowEvent {
        const uint32_t width, height;
        WindowResizeEvent(uint32_t width, uint32_t height) : width(width), height(height) {}
        operator std::string() const override;
        virtual bool Dispatch(EventListener& l) const override;
    };

    struct ASTRAL_API WindowFocusEvent : WindowEvent {
        operator std::string() const override;
        virtual bool Dispatch(EventListener& l) const override;
    };

    struct ASTRAL_API WindowLostFocusEvent : WindowEvent {
        operator std::string() const override;
        virtual bool Dispatch(EventListener& l) const override;
    };

    struct ASTRAL_API WindowMovedEvent : WindowEvent {
        const uint32_t x, y;
        WindowMovedEvent(uint32_t x, uint32_t y) : x(x), y(y) {}
        operator std::string() const override;
        virtual bool Dispatch(EventListener& l) const override;
    };

    struct ASTRAL_API AppTickEvent : AppEvent {
        operator std::string() const override;
        virtual bool Dispatch(EventListener& l) const override;
    };

    struct ASTRAL_API AppUpdateEvent : AppEvent {
        operator std::string() const override;
        virtual bool Dispatch(EventListener& l) const override;
    };

    struct ASTRAL_API AppRenderEvent : AppEvent {
        operator std::string() const override;
        virtual bool Dispatch(EventListener& l) const override;
    };

    struct ASTRAL_API KeyPressedEvent : InputEvent {
        const uint32_t keycode, repeatCount;
        KeyPressedEvent(uint32_t keycode, uint32_t repeatCount) : keycode(keycode), repeatCount(repeatCount) {}
        operator std::string() const override;
        virtual bool Dispatch(EventListener& l) const override;
    };

    struct ASTRAL_API KeyReleasedEvent : InputEvent {
        const uint32_t keycode;
        KeyReleasedEvent(uint32_t keycode) : keycode(keycode) {}
        operator std::string() const override;
        virtual bool Dispatch(EventListener& l) const override;
    };

    struct ASTRAL_API MouseButtonPressedEvent : InputEvent {
		const uint32_t button;
        const double x, y;
        MouseButtonPressedEvent(uint32_t button, double x, double y) : button(button), x(x), y(y) {}
        operator std::string() const override;
        virtual bool Dispatch(EventListener& l) const override;
    };

    struct ASTRAL_API MouseButtonReleasedEvent : InputEvent {
        const uint32_t button;
        const double x, y;
        MouseButtonReleasedEvent(uint32_t button, double x, double y) : button(button), x(x), y(y) {}
        operator std::string() const override;
        virtual bool Dispatch(EventListener& l) const override;
    };

    struct ASTRAL_API MouseMovedEvent : InputEvent {
        const double x, y;
        MouseMovedEvent(double x, double y) : x(x), y(y) {}
        operator std::string() const override;
        virtual bool Dispatch(EventListener& l) const override;
    };

    struct ASTRAL_API MouseScrolledEvent : InputEvent {
        const double xOffset, yOffset;
        MouseScrolledEvent(double xOffset, double yOffset) : xOffset(xOffset), yOffset(yOffset) {}
        operator std::string() const override;
        virtual bool Dispatch(EventListener& l) const override;
    };


    template<typename T>
    concept EventType = std::is_base_of_v<Event, T>;
}
