#include <Common.h>

#include "Event.h"
#include "EventDispatcher.h"

namespace Astral {

    void Event::Dispatch() const{
        EventDispatcher<Event>::DispatchWithoutHierarchy(*this);
    }

    Event::operator std::string() const {
        return "Event {}";
    }

    void WindowEvent::Dispatch() const{
        EventDispatcher<WindowEvent>::DispatchWithoutHierarchy(*this);
        Event::Dispatch();
    }

    WindowEvent::operator std::string() const {
        return "WindowEvent {}";
    }

    void AppEvent::Dispatch() const{
        EventDispatcher<AppEvent>::DispatchWithoutHierarchy(*this);
        Event::Dispatch();
    }

    AppEvent::operator std::string() const {
        return "AppEvent {}";
    }

    void InputEvent::Dispatch() const{
        EventDispatcher<InputEvent>::DispatchWithoutHierarchy(*this);
        Event::Dispatch();
    }

    InputEvent::operator std::string() const {
        return "InputEvent {}";
    }

    void WindowCloseEvent::Dispatch() const{
        EventDispatcher<WindowCloseEvent>::DispatchWithoutHierarchy(*this);
        WindowEvent::Dispatch();
    }

    WindowCloseEvent::operator std::string() const {
        return "WindowCloseEvent {}";
    }

    void WindowResizeEvent::Dispatch() const{
        EventDispatcher<WindowResizeEvent>::DispatchWithoutHierarchy(*this);
        WindowEvent::Dispatch();
    }

    WindowResizeEvent::operator std::string() const {
        return std::format("WindowResizeEvent {{ width = {0}, height = {1} }}", width, height);
    }

    void WindowFocusEvent::Dispatch() const{
        EventDispatcher<WindowFocusEvent>::DispatchWithoutHierarchy(*this);
        WindowEvent::Dispatch();
    }

    WindowFocusEvent::operator std::string() const {
        return "WindowFocusEvent";
    }

    void WindowLostFocusEvent::Dispatch() const{
        EventDispatcher<WindowLostFocusEvent>::DispatchWithoutHierarchy(*this);
        WindowEvent::Dispatch();
    }

    WindowLostFocusEvent::operator std::string() const {
        return "WindowLostFocusEvent";
    }

    void WindowMovedEvent::Dispatch() const{
        EventDispatcher<WindowMovedEvent>::DispatchWithoutHierarchy(*this);
        WindowEvent::Dispatch();
    }

    WindowMovedEvent::operator std::string() const {
        return std::format("WindowMovedEvent {{ x = {0}, y = {1} }}", x, y);
    }

    void AppTickEvent::Dispatch() const{
        EventDispatcher<AppTickEvent>::DispatchWithoutHierarchy(*this);
        AppEvent::Dispatch();
    }

    AppTickEvent::operator std::string() const {
        return "AppTickEvent";
    }

    void AppUpdateEvent::Dispatch() const{
        EventDispatcher<AppUpdateEvent>::DispatchWithoutHierarchy(*this);
        AppEvent::Dispatch();
    }

    AppUpdateEvent::operator std::string() const {
        return "AppUpdateEvent";
    }

    void AppRenderEvent::Dispatch() const {
        EventDispatcher<AppRenderEvent>::DispatchWithoutHierarchy(*this);
        AppEvent::Dispatch();
    }

    AppRenderEvent::operator std::string() const {
        return "AppRenderEvent";
    }

    void KeyPressedEvent::Dispatch() const{
        EventDispatcher<KeyPressedEvent>::DispatchWithoutHierarchy(*this);
        InputEvent::Dispatch();
    }

    KeyPressedEvent::operator std::string() const {
        return std::format("KeyPressedEvent {{ keycode = {0}, repeatCount = {1} }}", keycode, repeatCount);
    }

    void KeyReleasedEvent::Dispatch() const{
        EventDispatcher<KeyReleasedEvent>::DispatchWithoutHierarchy(*this);
        InputEvent::Dispatch();
    }

    KeyReleasedEvent::operator std::string() const {
        return std::format("KeyReleasedEvent {{ keycode = {0} }}", keycode);
    }

    void MouseButtonPressedEvent::Dispatch() const{
        EventDispatcher<MouseButtonPressedEvent>::DispatchWithoutHierarchy(*this);
        InputEvent::Dispatch();
    }

    MouseButtonPressedEvent::operator std::string() const {
        return std::format("MouseButtonPressedEvent {{ button = {0}, x = {1}, y = {2} }}", button, x, y);
    }

    void MouseButtonReleasedEvent::Dispatch() const{
        EventDispatcher<MouseButtonReleasedEvent>::DispatchWithoutHierarchy(*this);
        InputEvent::Dispatch();
    }

    MouseButtonReleasedEvent::operator std::string() const {
        return std::format("MouseButtonReleasedEvent {{ button = {0}, x = {1}, y = {2} }}", button, x, y);
    }

    void MouseMovedEvent::Dispatch() const{
        EventDispatcher<MouseMovedEvent>::DispatchWithoutHierarchy(*this);
        InputEvent::Dispatch();
    }

    MouseMovedEvent::operator std::string() const {
        return std::format("MouseMovedEvent {{ x = {0}, y = {1} }}", x, y);
    }

    void MouseScrolledEvent::Dispatch() const{
        EventDispatcher<MouseScrolledEvent>::DispatchWithoutHierarchy(*this);
        InputEvent::Dispatch();
    }

    MouseScrolledEvent::operator std::string() const {
        return std::format("MouseScrolledEvent {{ x = {0}, y = {1} }}", xOffset, yOffset);
    }
}
