#include <Common.h>

#include "Application.h"
#include "Astral/App/BootStrapper/BootStrapper.h"
#include "Astral/App/Layers/DebugLayer/DebugLayer.h"
#include "Astral/App/Layers/LayerStack/LayerStack.h"
#include "Astral/App/Events/Event/Event.h"
#include "Astral/App/FrameContext.h"
#include "Astral/Rendering/Renderer/Renderer.h"
#include "Astral/Assets/AssetRegistry/AssetRegistry.h"

namespace Astral::App {

	Application::Application(const StartupConfig& config) : 
		is_running(false), 
		active_scene(nullptr),
		window(WindowStartup(config)),
		renderer(&window, Render::API::OpenGL),
		assets(&renderer),
		layers(&assets)
	{
		SubscribeTo(window);
		layers.SubscribeTo(*this);

		layers.PushOverlay(std::make_unique<DebugLayer>(&renderer, [this] {
			layers.RenderImGuiWidgets();  // Inject ability to render debug widgets into debug layer
			}));

		// provided shader library

		// ========================================= FLAT SHADER ========================================
		Render::VertexAttribute position{
			.location = 0,
			.binding = 0,
			.format = Render::AttributeFormat::Float,
			.components = 3,
			.offset = offsetof(Assets::Vertex, position),
			.normalized = false
		};

		Render::VertexAttribute text_coord{
			.location = 1,
			.binding = 0,
			.format = Render::AttributeFormat::Float,
			.components = 2,
			.offset = offsetof(Assets::Vertex, text_coord),
			.normalized = false
		};

		Render::VertexBinding binding{
			.location = 0,
			.divisor = 0
		};

		Render::VertexLayout flat_layout{
			.attributes = { position, text_coord },
			.bindings = { binding }
		};

		Assets().CreateShader("Flat Shader", flat_layout, "src/Shaders/Flat/vertex.vert.glsl", "src/Shaders/Flat/fragment.frag.glsl");
	}

	void Application::SetActiveScene(Assets::Scene* scene) {
		active_scene = scene;
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
		AST_CORE_ASSERT(active_scene, "A Scene must be made active at simulation startup");
		is_running = true;
		window.PumpEvents();
		while (is_running) {
			FrameContext ctxt = window.GetFrameContext();
			Update(ctxt);
			layers.Update(ctxt);
			renderer.Command().NewFrame(0, ctxt.window_snapshot.frame_width, ctxt.window_snapshot.frame_height);
			active_scene->Draw(renderer, ctxt.window_snapshot.frame_width, ctxt.window_snapshot.frame_height);
			renderer.Command().SubmitFrame();
			window.PumpEvents();
		}
	}

	LayerStack& Application::Layers() {
		return layers;
	}

	Assets::AssetRegistry& Application::Assets() {
		return assets;
	}
}
