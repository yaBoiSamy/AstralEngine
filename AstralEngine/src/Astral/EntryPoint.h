#pragma once
#include "Application/Application.h"
#include "Logging/Log.h"

#ifdef AST_PLATFORM_WINDOWS

extern Astral::Application* Astral::CreateApplication();

int main(int argc, char** argv) {
	Astral::Log::Init();
	Astral::Application* app = Astral::CreateApplication();
	app->Run();
	delete app;
}

#endif