#include <Common.h>

#include "Application.h"
#include "Astral/Events/EventDispatcher.h"

namespace Astral {

	Application::Application() : window(std::make_unique<Window>()), isRunning(false) {
		EventDispatcher<WindowCloseEvent>::Subscribe([this](WindowCloseEvent event) {
			isRunning = false;
			});

		EventDispatcher<Event>::Subscribe([](Event const& event) {
			AST_CORE_INFO((std::string)event);
			});
	}

	Application::~Application() {}

	void Application::Run() {
		isRunning = true;
		while (isRunning) {
			window->Update();
		}
		window->~Window();
	}
}
