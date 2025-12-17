#include <Common.h>

#include "Event.h"

namespace Astral {
    std::string ToString(const Event& event) {
        return std::visit(overloaded{
            [](const WindowClose&) {
                return std::string("WindowClose");
            },

            [](const WindowResize& e) {
                return std::format("WindowResize({}, {})", e.width, e.height);
            },

            [](const WindowFocus&) {
                return std::string("WindowFocus");
            },

            [](const WindowLostFocus&) {
                return std::string("WindowLostFocus");
            },

            [](const WindowMoved& e) {
                return std::format("WindowMoved({}, {})", e.x, e.y);
            },

            [](const AppTick&) {
                return std::string("AppTick");
            },

            [](const AppUpdate&) {
                return std::string("AppUpdate");
            },

            [](const AppRender&) {
                return std::string("AppRender");
            },

            [](const KeyPressed& e) {
                return std::format("KeyPressed(key={}, repeat={})", e.keycode, e.repeatCount);
            },

            [](const KeyReleased& e) {
                return std::format("KeyReleased(key={})", e.keycode);
            },

            [](const MouseButtonPressed& e) {
                return std::format("MouseButtonPressed(button={}, x={}, y={})", e.button, e.x, e.y);
            },

            [](const MouseButtonReleased& e) {
                return std::format("MouseButtonReleased(button={}, x={}, y={})", e.button, e.x, e.y);
            },

            [](const MouseMoved& e) {
                return std::format("MouseMoved(x={}, y={})", e.x, e.y);
            },

            [](const MouseScrolled& e) {
                return std::format("MouseScrolled(xOffset={}, yOffset={})", e.xOffset, e.yOffset);
            }
            }, event);
    }

}
