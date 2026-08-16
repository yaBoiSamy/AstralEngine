#pragma once
#include "Astral/App/Window/Window.h"

namespace Astral::App {

	struct StartupConfig {
		// Window Parameters
		std::string window_name = "AstralEngine";
		uint32_t window_width = 1920;
		uint32_t window_height = 1080;
		bool vsync = true;

		// Graphics API	parameters
		int gl_major = 4;
		int gl_minor = 6;
	};

	Window WindowStartup(const StartupConfig& startupConfig);
}