#pragma once

#include "Astral/Core.h"

namespace Astral {

	class ASTRAL_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined by user
	Application* CreateApplication();
}