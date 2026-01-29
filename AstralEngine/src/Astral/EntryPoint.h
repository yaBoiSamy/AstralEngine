#pragma once
#include "Application/Application.h"
#include "Logging/Log.h"
#include "BootStrapper/BootStrapper.h"

#ifdef AST_PLATFORM_WINDOWS

extern Astral::Application* Astral::CreateApplication(StartupConfig& config);

int main(int argc, char** argv) {

	Astral::StartupConfig startupConfig{
		// Window Parameters
		"AstralEngine", // window name
		1920,  // resolution width
		1080,  // resolution height
		true,  // vSync

		// Graphics API	parameters
		3,  // gl major
		3,  // gl minor
	};

	Astral::Log::Init();
	Astral::Application* app = Astral::CreateApplication(startupConfig);
	app->Run();
	delete app;
}

#endif