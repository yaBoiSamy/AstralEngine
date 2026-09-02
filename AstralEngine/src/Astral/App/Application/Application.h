#pragma once

#include "Astral/App/Window/Window.h"
#include "Astral/App/FrameContext.h"
#include "Astral/App/Layers/LayerStack/LayerStack.h"
#include "Astral/App/Events/EventHandlers/EventHandlers.h"
#include "Astral/App/Application/StartupConfig.h"
#include "Astral/Rendering/Renderer/Renderer.h"
#include "Astral/Assets/AssetRegistry/AssetRegistry.h"


namespace Astral::App {
	class Application : public EventListener, public EventBroadcaster {
	public:
		Application(const App::StartupConfig& config);

		virtual void Update(const FrameContext& context) {};

		void Close();
		void Run();

		LayerStack& Layers();
		Assets::AssetRegistry& Assets();
	private:
		virtual bool OnEvent(const Event& event) final;
		virtual bool OnWindowCloseEvent(const WindowCloseEvent& event) final;

		bool is_running;
		Assets::Scene* active_scene;

		Window window;
		Render::Renderer renderer;
		Assets::AssetRegistry assets;
		LayerStack layers;
	};

	// To be defined by user
	Application* CreateApplication(StartupConfig& config);
}
