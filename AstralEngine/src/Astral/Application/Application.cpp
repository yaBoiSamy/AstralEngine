#include <Common.h>

#include "Application.h"

namespace Astral {

	Application::Application() : window(std::make_unique<Window>()), isRunning(false) {}

	Application::~Application() {}

	void Application::Run() {
		isRunning = true;
		while (isRunning) {
			window->Update();
		}
	}
}
