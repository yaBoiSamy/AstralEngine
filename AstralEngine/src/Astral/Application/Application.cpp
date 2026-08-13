#include <Common.h>

#include "Application.h"
#include "Astral/BootStrapper/BootStrapper.h"
#include "Astral/Model/Layers/DebugLayer/DebugLayer.h"
#include "Astral/Model/Layers/MainLayer/MainLayer.h"
#include "Astral/Rendering/Renderer/Renderer.h"
#include "Astral/Rendering/Shader/ShaderLibrary.h"

namespace Astral {

	Application::Application(const StartupConfig& config) : is_running(false), window(WindowStartup(config)) {
		SubscribeTo(window);
		layers.SubscribeTo(*this);

		Renderer::InitRenderer();

		layers.PushOverlay(std::make_unique<DebugLayer>([this] {
			layers.RenderImGuiWidgets();  // Inject ability to render debug widgets into debug layer
			}));

		layers.PushLayer(std::make_unique<MainLayer>());

		shaderlib.Load("Flat Shader", "src/Shaders/vertex.vert.glsl", "src/Shaders/fragment.frag.glsl");
	}

	bool Application::OnWindowCloseEvent(const WindowCloseEvent& event) {
		AST_CORE_INFO("Window close event received, closing application.");
		is_running = false;
		return true;
	}

	bool Application::OnEvent(const Event& event) {
		return Broadcast(event);
	}

	FrameContext Application::GetFrameContext() const {
		return window.GetFrameContext();
	}

	void Application::Close() {
		AST_CORE_INFO("App closed"); is_running = false;
	};

	void Application::Run() {
		is_running = true;
		window.PumpEvents();
		while (is_running) {
			FrameContext ctxt = GetFrameContext();
			Renderer::SetupFrame(ctxt.window_snapshot.frame_width, ctxt.window_snapshot.frame_height);
			Update();
			layers.Update(ctxt);
			window.SwapBuffers(); // present frame
			window.PumpEvents();
		}
	}
}
