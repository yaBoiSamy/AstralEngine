#pragma once

#include "Astral/Window/Window.h"
#include "Astral/BootStrapper/BootStrapper.h"
#include "Astral/Model/Layers/LayerStack/LayerStack.h"
#include "Astral/Events/EventHandlers/EventHandlers.h"
#include "Astral/Rendering/Shader/ShaderLibrary.h"

namespace Astral {
	class Application : public EventListener, public EventBroadcaster {
	public:
		Application(const StartupConfig& config);

		virtual void Update() {};   // User-space simulation updates

		FrameContext GetFrameContext() const;

		void Close();
		void Run();

		LayerStack layers;
	protected:
		ShaderLibrary shaderlib;

	private:
		virtual bool OnEvent(const Event& event) final;
		virtual bool OnWindowCloseEvent(const WindowCloseEvent& event) final;

		bool is_running;
		Window window;
	};

	// To be defined by user
	Application* CreateApplication(StartupConfig& config);
}
