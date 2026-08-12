#include <Common.h>
//#include <GLFW/glfw3.h>

#include "Application.h"
#include "Astral/BootStrapper/BootStrapper.h"
#include "Astral/Layers/DebugLayer/DebugLayer.h"
#include "Astral/Layers/GLSLLayer/GLSLLayer.h"
#include "Astral/Rendering/Renderer/Renderer.h"
#include "Astral/Rendering/Shader/ShaderLibrary.h"

namespace Astral {

	Application::Application(const StartupConfig& config) : isRunning(false), window(WindowStartup(config)) {
		window.SetCallback([this](const Event& event) {
			event.Dispatch(*this);
			layers.PropagateEvent(event);
			});

		Renderer::InitRenderer();

		layers.PushOverlay(std::make_unique<DebugLayer>([this] {
			layers.RenderImGuiWidgets();  // Inject ability to render debug widgets into debug layer
			}));

		layers.PushLayer(std::make_unique<GLSLLayer>());

		shaderlib.Load("Flat Shader", "src/Shaders/vertex.vert.glsl", "src/Shaders/fragment.frag.glsl");
	}

	bool Application::OnWindowCloseEvent(const WindowCloseEvent& event) {
		AST_CORE_INFO("Window close event received, closing application.");
		isRunning = false;
		return true;
	}

	FrameContext Application::GetFrameContext() const {
		return window.GetFrameContext();
	}

	void Application::Close() {
		AST_CORE_INFO("App closed"); isRunning = false;
	};

	void Application::Run() {
		isRunning = true;
		while (isRunning) {
			window.PumpEvents();
			Renderer::SetupFrame(window.GetFramebufferSize());
			Update();
			layers.Update(GetFrameContext());
			window.SwapBuffers(); // present frame
		}
	}
}
