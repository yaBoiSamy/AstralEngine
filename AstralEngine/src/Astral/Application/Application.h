#pragma once

#include "Astral/Window/Window.h"
#include "Astral/Renderer/Renderer.h"
#include "Astral/BootStrapper/BootStrapper.h"
#include "Astral/Layers/LayerStack.h"
#include "Astral/Events/EventListener.h"

namespace Astral {
	class Application : public EventListener {
	public:
		Application(const StartupConfig& config);
		virtual ~Application();

		virtual void Start() {};
		virtual void Update() {};   // User-space simulation updates
		void Close() { 
			AST_CORE_INFO("App closed"); isRunning = false; 
		};
		void Run();

	private:
		virtual bool OnWindowCloseEvent(const WindowCloseEvent& event) final;

		bool isRunning;
		Window window;
		Renderer renderer;
		LayerStack layers;
	};

	// To be defined by user
	Application* CreateApplication(StartupConfig& config);
}
