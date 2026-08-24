#include "Common.h"
#include "Renderer.h"


namespace Astral::Render {
	Renderer::Renderer(App::Window* window, API graphics_api) :
		pipe(std::make_shared<Render::Pipe>()),
		invoker(pipe->CreateInvoker()),
		executor_thread(
			[this, window, graphics_api](std::stop_token stop) {
				Render::Executor executor = pipe->CreateExecutor(window, graphics_api);
				while (!stop.stop_requested()) {
					executor.ExecuteCommands();
				}
			}
		) 
	{
		lighting_handle = invoker.CreateUniformBuffer(sizeof(LightingData));
		camera_handle = invoker.CreateUniformBuffer(sizeof(CameraData));
		model_handle = invoker.CreateUniformBuffer(sizeof(ModelData));
	}

	const Invoker& Renderer::Command() const {
		return invoker;
	}

	void Renderer::UpdateLightingData(LightingData lighting_data) const {
		ByteBox bytes = ToBytes(std::make_unique<LightingData>(std::move(lighting_data)));
		invoker.WriteUniformBuffer(lighting_handle, std::move(bytes));
	}

	void Renderer::UpdateCameraData(CameraData camera_data) const {
		ByteBox bytes = ToBytes(std::make_unique<CameraData>(std::move(camera_data)));
		invoker.WriteUniformBuffer(camera_handle, std::move(bytes));
	}

	void Renderer::UpdateModelData(ModelData model_data) const {
		ByteBox bytes = ToBytes(std::make_unique<ModelData>(std::move(model_data)));
		invoker.WriteUniformBuffer(model_handle, std::move(bytes));
	}

	std::vector<ResourceBinding> Renderer::GetBindings() const {
		UniformBufferBinding lighting_binding{
			.binding_slot = LIGHTING_BINDING_SLOT,
			.resource = lighting_handle
		};
		UniformBufferBinding camera_binding{
			.binding_slot = CAMERA_BINDING_SLOT,
			.resource = camera_handle
		};
		UniformBufferBinding model_binding{
			.binding_slot = MODEL_BINDING_SLOT,
			.resource = model_handle
		};
		return { lighting_binding, camera_binding, model_binding };
	}
}