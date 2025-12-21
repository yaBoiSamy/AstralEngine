#pragma once

#include "Astral/Core.h"
#include "Astral/Window/Window.h"

namespace Astral {
	class ASTRAL_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();
		
	private:
		std::unique_ptr<Window> window;
		bool isRunning;
	};

	// To be defined by user
	Application* CreateApplication();
}