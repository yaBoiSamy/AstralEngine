#include <Common.h>

#include "Application.h"
#include "Astral/Events/EventDispatcher.h"

namespace Astral {

	Application::Application() : window(std::make_unique<Window>()), isRunning(false) {
		EventDispatcher<WindowCloseEvent>::Subscribe([this](WindowCloseEvent const& event) {
			isRunning = false;
			});

		EventDispatcher<KeyPressedEvent>::Subscribe([this](KeyPressedEvent const& event) {
			OnKeyPressed(event.keycode, event.repeatCount);
			});

		EventDispatcher<KeyReleasedEvent>::Subscribe([this](KeyReleasedEvent const& event) {
			OnKeyReleased(event.keycode);
			});

		EventDispatcher<MouseButtonPressedEvent>::Subscribe([this](MouseButtonPressedEvent const& event) {
			OnMouseButtonPressed(event.button, event.x, event.y);
			});

		EventDispatcher<MouseButtonReleasedEvent>::Subscribe([this](MouseButtonReleasedEvent const& event) {
			OnMouseButtonReleased(event.button, event.x, event.y);
			});

		EventDispatcher<MouseMovedEvent>::Subscribe([this](MouseMovedEvent const& event) {
			OnMouseMoved(event.x, event.y);
			});
	}

	Application::~Application() {}

	void Application::Run() {
		isRunning = true;
		Start();
		while (isRunning) {
			window->Update();
			Update();
		}
		window->~Window();
	}

}
