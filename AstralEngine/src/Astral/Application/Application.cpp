#include <Common.h>

#include "Application.h"
#include "Astral/BootStrapper/BootStrapper.h"
#include "Astral/Layers/DebugLayer/DebugLayer.h"
#include "Astral/Layers/TestRenderLayer/TestRenderLayer.h"

namespace Astral {

	Application::Application(const StartupConfig& config) : isRunning(false), window(WindowStartup(config)) {
		window.SetCallback([this](const Event& event) {
			event.Dispatch(*this);
			layers.PropagateEvent(event);
			});

		layers.PushOverlay(std::make_unique<DebugLayer>([this] {
			layers.RenderImGuiWidgets();  // Inject ability to render debug widgets into debug layer
			}));

		layers.PushLayer(std::make_unique<TestRenderLayer>());
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
			Update();
			window.PumpEvents();
			renderer.SetupFrame(window.GetFramebufferSize());
			layers.Update(window.GetFrameContext());
			renderer.PresentFrame(window);
		}
	}
}
