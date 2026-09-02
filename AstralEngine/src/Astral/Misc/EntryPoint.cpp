#include "Common.h"
#include "Astral/Misc/Log/Log.h"
#include "Astral/App/Application/Application.h"
#include "Astral/App/Application/StartupConfig.h"

#ifdef AST_PLATFORM_WINDOWS

extern Astral::App::Application* Astral::App::CreateApplication(StartupConfig& config);

int main(int argc, char** argv) {

	Astral::App::StartupConfig startup_config{
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
	Astral::App::Application* app = Astral::App::CreateApplication(startup_config);
	app->Run();
	delete app;
}

#endif