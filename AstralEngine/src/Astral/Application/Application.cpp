#include <Common.h>

#include "Application.h"
#include "Astral/BootStrapper/BootStrapper.h"
#include "Astral/Layers/DebugLayer/DebugLayer.h"

namespace Astral {

	Application::Application(const StartupConfig& config) : isRunning(false), window(WindowStartup(config)) {
		window.SetCallback([this](const Event& event) {
			event.Dispatch(*this);
			layers.PropagateEvent(event);
			});

		layers.PushOverlay(
			std::make_unique<DebugLayer>(
				[this]() { return window.GetDeltaTime(); },
				[this]() { return window.GetState(); }
			)
		);
	}

	bool Application::OnWindowCloseEvent(const WindowCloseEvent& event) {
		AST_CORE_INFO("Window close event received, closing application.");
		isRunning = false;
		return true;
	}

	Application::~Application() {}

	void Application::Run() {
		isRunning = true;
		Start();
		while (isRunning) {
			window.Update();
			layers.Update();
			Update();
		}
	}

}
