#pragma once

#include <Common.h>

namespace Astral {

    struct WindowClose {};

    struct WindowResize {
        const uint32_t width, height;
        WindowResize(uint32_t width, uint32_t height) : width(width), height(height) {}
    };

    struct WindowFocus {};

    struct WindowLostFocus {};

    struct WindowMoved {
        const uint32_t x, y;
        WindowMoved(uint32_t x, uint32_t y) : x(x), y(y) {}
    };

    struct AppTick {};

    struct AppUpdate {};

    struct AppRender {};

    struct KeyPressed {
        const uint32_t keycode, repeatCount;
        KeyPressed(uint32_t keycode, uint32_t repeatCount) : keycode(keycode), repeatCount(repeatCount) {}
    };

    struct KeyReleased {
        const uint32_t keycode;
        KeyReleased(uint32_t keycode) : keycode(keycode) {}
    };

    struct MouseButtonPressed {
        const uint32_t button, x, y;
        MouseButtonPressed(uint32_t button, uint32_t x, uint32_t y) : button(button), x(x), y(y) {}
    };

    struct MouseButtonReleased {
        const uint32_t button, x, y;
        MouseButtonReleased(uint32_t button, uint32_t x, uint32_t y) : button(button), x(x), y(y) {}
    };

    struct MouseMoved {
        const float x, y;
        MouseMoved(float x, float y) : x(x), y(y) {}
    };

    struct MouseScrolled {
        const float xOffset, yOffset;
        MouseScrolled(float xOffset, float yOffset) : xOffset(xOffset), yOffset(yOffset) {}
    };


    using Event = std::variant<
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    >;

    using WindowEvent = std::variant<
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved
    >;

    using AppEvent = std::variant<
        AppTick, AppUpdate, AppRender
    >;

    using InputEvent = std::variant<
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    >;


    std::string ToString(Event& event);
}
