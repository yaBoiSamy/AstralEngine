#include <Common.h>

#include "Application.h"
#include "Astral/App/BootStrapper/BootStrapper.h"
#include "Astral/App/Layers/DebugLayer/DebugLayer.h"
#include "Astral/App/Layers/LayerStack/LayerStack.h"
#include "Astral/App/Events/Event/Event.h"
#include "Astral/App/FrameContext.h"
#include "Astral/Rendering/Renderer/Renderer.h"
#include "Astral/Assets/AssetRegistry.h"
#include "Astral/Assets/Shader/Shader.h"

namespace Astral::App {
	using namespace Render;
	using namespace Assets;

	Application::Application(const StartupConfig& config) : is_running(false), window(WindowStartup(config)), layers(&assets) {
		SubscribeTo(window);
		layers.SubscribeTo(*this);

		Renderer::InitRenderer();

		layers.PushOverlay(std::make_unique<DebugLayer>([this] {
			layers.RenderImGuiWidgets();  // Inject ability to render debug widgets into debug layer
			}));

		// provided shader library
		Box<Assets::Shader> shader = std::make_unique<Assets::Shader>("Flat Shader", "src/Shaders/Flat/vertex.vert.glsl", "src/Shaders/Flat/fragment.frag.glsl");
		Assets().Load(std::move(shader));
	}

	bool Application::OnWindowCloseEvent(const WindowCloseEvent& event) {
		AST_CORE_INFO("Window close event received, closing application.");
		is_running = false;
		return true;
	}

	bool Application::OnEvent(const Event& event) {
		return Broadcast(event);
	}

	void Application::Close() {
		AST_CORE_INFO("App closed"); is_running = false;
	};

	void Application::Run() {
		is_running = true;
		window.PumpEvents();
		while (is_running) {
			FrameContext ctxt = window.GetFrameContext();
			Renderer::SetupFrame(ctxt.window_snapshot.frame_width, ctxt.window_snapshot.frame_height);
			Update(ctxt);
			layers.Update(ctxt);
			window.SwapBuffers(); // present frame
			window.PumpEvents();
		}
	}

	LayerStack& Application::Layers() {
		return layers;
	}

	AssetRegistry& Application::Assets() {
		return assets;
	}
}
