#pragma once

#include "Astral/Window/Window.h"
#include "Astral/BootStrapper/BootStrapper.h"
#include "Astral/Layers/LayerStack.h"
#include "Astral/Events/EventListener.h"
#include "Astral/Rendering/Shader/ShaderLibrary.h"

namespace Astral {
	class Application : public EventListener {
	public:
		Application(const StartupConfig& config);

		virtual void Update() {};   // User-space simulation updates

		FrameContext GetFrameContext() const;

		void Close();
		void Run();

	protected:
		ShaderLibrary shaderlib;

	private:
		virtual bool OnWindowCloseEvent(const WindowCloseEvent& event) final;

		bool isRunning;
		Window window;
		LayerStack layers;
	};

	// To be defined by user
	Application* CreateApplication(StartupConfig& config);
}
