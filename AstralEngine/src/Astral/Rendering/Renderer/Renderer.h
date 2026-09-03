#pragma once
#include "Common.h"
#include "Astral/Rendering/Pipe/Pipe.h"
#include "Astral/Rendering/Renderer/Renderer.h"
#include "Astral/Rendering/Pipe/Executor/Executor.h"
#include "Astral/Rendering/Pipe/Command/Command.h"
#include "Astral/App/Application/StartupConfig.h"


namespace Astral::Render {
	class Renderer {
	public:
		Renderer(App::Window* window, API graphics_api, const App::StartupConfig& config);
		const Invoker& Command() const;

		void UpdateViewportData(uint32_t width, uint32_t height) const;
		void UpdateLightingData() const;
		void UpdateCameraData(const glm::mat4& view, const glm::mat4& projection) const;
		void UpdateModelData(const glm::mat4& model) const ;

		std::vector<ResourceBinding> GetBindings() const;

	private:
		Arc<Pipe> pipe;
		Invoker invoker;
		std::jthread executor_thread;

		ResourceHandle viewport_handle;
		ResourceHandle lighting_handle;
		ResourceHandle camera_handle;
		ResourceHandle model_handle;

		const uint32_t VIEWPORT_BINDING_SLOT = 0;
		const uint32_t LIGHTING_BINDING_SLOT = 1;
		const uint32_t CAMERA_BINDING_SLOT = 2;
		const uint32_t MODEL_BINDING_SLOT = 3;
	};
}

