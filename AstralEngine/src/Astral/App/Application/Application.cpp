#include <Common.h>
#define TRACY_ENABLE
#include <tracy/Tracy.hpp>

#include "Application.h"
#include "Astral/App/Layers/UILayer/UILayer.h"
#include "Astral/App/Layers/DebugLayer/DebugLayer.h"
#include "Astral/App/Layers/LayerStack/LayerStack.h"
#include "Astral/App/Events/Event/Event.h"
#include "Astral/App/FrameContext.h"
#include "Astral/Rendering/Renderer/Renderer.h"
#include "Astral/Assets/AssetRegistry/AssetRegistry.h"

namespace Astral::App {

	Application::Application(const App::StartupConfig& config) : 
		is_running(false), 
		active_scene(nullptr),
		window(config),
		renderer(&window, Render::API::OpenGL, config),
		assets(&renderer),
		layers(&assets)
	{
		SubscribeTo(window);
		layers.SubscribeTo(*this);

		layers.PushLayer(std::make_unique<DebugLayer>(this, &renderer));

		layers.PushOverlay(std::make_unique<UILayer>(this, &renderer, [this] {
			layers.RenderImGuiWidgets();  // Inject ability to render debug widgets into debug layer
		}));


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

		Assets().CreateShader("Flat", flat_layout, "src/Shaders/Flat/vertex.vert.glsl", "src/Shaders/Flat/fragment.frag.glsl");


		// ========================================= BILLBOARD =========================================

		Assets().CreateMesh("Billboard", {
			{ { -0.5f, -0.5f, 0.0f }, { 0, 0 } },
			{ {  0.5f, -0.5f, 0.0f }, { 1, 0 } },
			{ {  0.5f,  0.5f, 0.0f }, { 1, 1 } },
			{ { -0.5f,  0.5f, 0.0f }, { 0, 1 } }
			}, {
				0, 1, 2,
				2, 3, 0
			}
		);
	}


	bool Application::OnWindowCloseEvent(const WindowCloseEvent& event) {
		AST_CORE_INFO("Window close event received, closing application.");
		is_running = false;
		return true;
	}

	bool Application::OnEvent(const Event& event) {
		return Broadcast(event);
	}

	void Application::SetCursorEnabled(bool is_enabled) {
		window.SetCursorEnabled(is_enabled);
	}

	void Application::Close() {
		AST_CORE_INFO("App closed"); is_running = false;
	};








	void Application::Run() {
		is_running = true;
		window.PumpEvents();
		while (is_running) {
			ZoneScoped;
			FrameContext ctxt = window.GetFrameContext();
			renderer.UpdateViewportData(ctxt.window_snapshot.frame_width, ctxt.window_snapshot.frame_height);
			renderer.Command().NewFrame(0, ctxt.window_snapshot.frame_width, ctxt.window_snapshot.frame_height);
			{
				ZoneScopedN("Application Update");
				Update(ctxt);
			} {
				ZoneScopedN("LayerStack Update");
				layers.Update(ctxt);
			} {
				ZoneScopedN("GPU bottlenecking");
				renderer.Command().SubmitFrame();
			}
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
