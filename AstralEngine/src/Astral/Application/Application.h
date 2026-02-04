#pragma once

#include "Astral/Core.h"
#include "Astral/Window/Window.h"
#include "Astral/BootStrapper/BootStrapper.h"
#include "Astral/Layers/LayerStack.h"
#include "Astral/Events/EventListener.h"

namespace Astral {
	class ASTRAL_API Application : public EventListener {
	public:
		Application(const StartupConfig& config);
		virtual ~Application();

		virtual void Start() {};
		virtual void Update() {};
		void Close() { AST_CORE_INFO("App closed"); isRunning = false; };
		void Run();

	private:
		virtual bool OnWindowCloseEvent(const WindowCloseEvent& event) final;

		bool isRunning;
		Window window;
		LayerStack layers;
	};

	// To be defined by user
	Application* CreateApplication(StartupConfig& config);
}
