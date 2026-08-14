#pragma once
#include "Application/Application.h"
#include "Logging/Log.h"
#include "BootStrapper/BootStrapper.h"

#ifdef AST_PLATFORM_WINDOWS

extern Astral::Application* Astral::CreateApplication(StartupConfig& config);

int main(int argc, char** argv) {

	Astral::StartupConfig startup_config{
		// Window Parameters
		"AstralEngine", // window name
		1920,  // window width
		1080,  // window height
		true,  // vsync

		// Graphics API	parameters
		4,  // gl major
		6,  // gl minor
	};

	Astral::Log::Init();
	Astral::Application* app = Astral::CreateApplication(startup_config);
	app->Run();
	delete app;
}

#endif