#pragma once

#include "Astral/App/Window/Window.h"
#include "Astral/App/FrameContext.h"
#include "Astral/App/BootStrapper/BootStrapper.h"
#include "Astral/App/Layers/LayerStack/LayerStack.h"
#include "Astral/App/Events/EventHandlers/EventHandlers.h"
#include "Astral/Rendering/Invoker/Invoker.h"
#include "Astral/Rendering/Command/CommandBuffer/CommandBuffer.h"
#include "Astral/Assets/AssetRegistry.h"


namespace Astral::App {

	class Application : public EventListener, public EventBroadcaster {
	public:
		Application(const StartupConfig& config);

		virtual void Update(const FrameContext& context) {};

		void Close();
		void Run();

		LayerStack& Layers();
		Assets::AssetRegistry& Assets();
	private:
		virtual bool OnEvent(const Event& event) final;
		virtual bool OnWindowCloseEvent(const WindowCloseEvent& event) final;

		bool is_running;
		Window window;
		Assets::AssetRegistry assets;
		LayerStack layers;

		Render::Invoker renderer_invoker;
		Arc<Render::CommandBuffer> renderer_command_buffer;
		std::jthread renderer_executor_thread;
	};

	// To be defined by user
	Application* CreateApplication(StartupConfig& config);
}
