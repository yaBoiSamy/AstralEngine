#pragma once
#include "Astral/Window/Window.h"

namespace Astral {

	ASTRAL_API struct StartupConfig {
		// Window Parameters
		std::string windowName = "AstralEngine";
		uint32_t resolutionWidth = 1920;
		uint32_t resolutionHeight = 1080;
		bool vSync = true;

		// Graphics API	parameters
		int glMajor = 3;
		int glMinor = 3;
	};

	ASTRAL_API Window WindowStartup(const StartupConfig& startupConfig);
}