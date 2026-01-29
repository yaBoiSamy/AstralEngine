#pragma once
#include <Common.h>
#include "Astral/Core.h" 
#include "Astral/Events/EventListener.h"

namespace Astral {
    template<typename E>
    struct EventDispatchKey;
    class EventListener;

	// Concrete events gain dispatch access through CRTP
	template<typename DerivedEvent>
    struct Dispatchable {
    protected:
        bool DispatchImpl(EventListener& l) const {
            return EventDispatchKey<DerivedEvent>::Dispatch(
                static_cast<const DerivedEvent&>(*this), l
            ); 
        }
    };

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

    struct ASTRAL_API WindowCloseEvent : WindowEvent, Dispatchable<WindowCloseEvent> {
        operator std::string() const override;
        virtual bool Dispatch(EventListener& l) const override;
    };

    struct ASTRAL_API WindowResizeEvent : WindowEvent, Dispatchable<WindowResizeEvent> {
        const uint32_t width, height;
        WindowResizeEvent(uint32_t width, uint32_t height) : width(width), height(height) {}
        operator std::string() const override;
        virtual bool Dispatch(EventListener& l) const override;
    };

    struct ASTRAL_API WindowFocusEvent : WindowEvent, Dispatchable<WindowFocusEvent> {
        operator std::string() const override;
        virtual bool Dispatch(EventListener& l) const override;
    };

    struct ASTRAL_API WindowLostFocusEvent : WindowEvent, Dispatchable<WindowLostFocusEvent> {
        operator std::string() const override;
        virtual bool Dispatch(EventListener& l) const override;
    };

    struct ASTRAL_API WindowMovedEvent : WindowEvent, Dispatchable<WindowMovedEvent> {
        const uint32_t x, y;
        WindowMovedEvent(uint32_t x, uint32_t y) : x(x), y(y) {}
        operator std::string() const override;
        virtual bool Dispatch(EventListener& l) const override;
    };

    struct ASTRAL_API AppTickEvent : AppEvent, Dispatchable<AppTickEvent> {
        operator std::string() const override;
        virtual bool Dispatch(EventListener& l) const override;
    };

    struct ASTRAL_API AppUpdateEvent : AppEvent, Dispatchable<AppUpdateEvent> {
        operator std::string() const override;
        virtual bool Dispatch(EventListener& l) const override;
    };

    struct ASTRAL_API AppRenderEvent : AppEvent, Dispatchable<AppRenderEvent> {
        operator std::string() const override;
        virtual bool Dispatch(EventListener& l) const override;
    };

    struct ASTRAL_API KeyPressedEvent : InputEvent, Dispatchable<KeyPressedEvent> {
        const uint32_t keycode, repeatCount;
        KeyPressedEvent(uint32_t keycode, uint32_t repeatCount) : keycode(keycode), repeatCount(repeatCount) {}
        operator std::string() const override;
        virtual bool Dispatch(EventListener& l) const override;
    };

    struct ASTRAL_API KeyReleasedEvent : InputEvent, Dispatchable<KeyReleasedEvent> {
        const uint32_t keycode;
        KeyReleasedEvent(uint32_t keycode) : keycode(keycode) {}
        operator std::string() const override;
        virtual bool Dispatch(EventListener& l) const override;
    };

    struct ASTRAL_API MouseButtonPressedEvent : InputEvent, Dispatchable<MouseButtonPressedEvent> {
        const double button, x, y;
        MouseButtonPressedEvent(uint32_t button, double x, double y) : button(button), x(x), y(y) {}
        operator std::string() const override;
        virtual bool Dispatch(EventListener& l) const override;
    };

    struct ASTRAL_API MouseButtonReleasedEvent : InputEvent, Dispatchable<MouseButtonReleasedEvent> {
        const uint32_t button;
        const double x, y;
        MouseButtonReleasedEvent(uint32_t button, double x, double y) : button(button), x(x), y(y) {}
        operator std::string() const override;
        virtual bool Dispatch(EventListener& l) const override;
    };

    struct ASTRAL_API MouseMovedEvent : InputEvent, Dispatchable<MouseMovedEvent> {
        const double x, y;
        MouseMovedEvent(double x, double y) : x(x), y(y) {}
        operator std::string() const override;
        virtual bool Dispatch(EventListener& l) const override;
    };

    struct ASTRAL_API MouseScrolledEvent : InputEvent, Dispatchable<MouseScrolledEvent> {
        const double xOffset, yOffset;
        MouseScrolledEvent(double xOffset, double yOffset) : xOffset(xOffset), yOffset(yOffset) {}
        operator std::string() const override;
        virtual bool Dispatch(EventListener& l) const override;
    };
}
