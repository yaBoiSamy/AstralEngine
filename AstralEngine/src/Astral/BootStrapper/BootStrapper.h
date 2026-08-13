#pragma once
#include "Astral/Window/Window.h"

namespace Astral {

	struct StartupConfig {
		// Window Parameters
		std::string windowName = "AstralEngine";
		uint32_t window_width = 1920;
		uint32_t window_height = 1080;
		bool vsync = true;

		// Graphics API	parameters
		int glMajor = 4;
		int glMinor = 6;
	};

	Window WindowStartup(const StartupConfig& startupConfig);
}