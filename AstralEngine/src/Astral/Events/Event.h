#pragma once

#include <Common.h>


struct WindowClose {};

struct WindowResize { 
    const int width, height;
    WindowResize(int width, int height) : width(width), height(height) {}
};

struct WindowFocus {};

struct WindowLostFocus {};

struct WindowMoved { 
    const int x, y; 
    WindowMoved(int x, int y) : x(x), y(y) {}
};

struct AppTick {};

struct AppUpdate {};

struct AppRender {};

struct KeyPressed {	
    const int keycode, repeatCount;
    KeyPressed(int keycode, int repeatCount) : keycode(keycode), repeatCount(repeatCount) {}
};

struct KeyReleased { 
    const int keycode;
    KeyReleased(int keycode) : keycode(keycode) {}
};

struct MouseButtonPressed {	
    const int button, x, y;
    MouseButtonPressed(int button, int x, int y) : button(button), x(x), y(y) {}
};

struct MouseButtonReleased { 
    const int button, x, y;
    MouseButtonReleased(int button, int x, int y) : button(button), x(x), y(y) {}
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
