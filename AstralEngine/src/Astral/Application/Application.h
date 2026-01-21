#pragma once

#include "Astral/Core.h"
#include "Astral/Window/Window.h"
#include "Astral/BootStrapper/BootStrapper.h"

namespace Astral {
	class ASTRAL_API Application {
	public:
		Application(const StartupConfig& config);
		virtual ~Application();

		virtual void Start() {};
		virtual void Update() {};
		void Close() { AST_CORE_INFO("App closed"); isRunning = false; };
		void Run();

		virtual void OnKeyPressed(uint32_t keycode, uint32_t repeatCount) {};
		virtual void OnKeyReleased(uint32_t keycode) {};
		
		virtual void OnMouseButtonPressed(uint32_t button, double x, double y) {};
		virtual void OnMouseButtonReleased(uint32_t button, double x, double y) {};

		virtual void OnMouseMoved(double x, double y) {};

	private:
		bool isRunning;
		Window window;
	};

	// To be defined by user
	Application* CreateApplication(StartupConfig& config);
}
