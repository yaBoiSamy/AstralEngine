#include "Common.h"
#include "Renderer.h"
#include "Astral/App/Application/StartupConfig.h"


extern thread_local std::stop_token cancellation_token;

namespace Astral::Render {

	struct ViewportData {
		uint32_t width;
		uint32_t height;
	};

	struct LightingData {};

	struct CameraData {
		glm::mat4 view;
		glm::mat4 projection;
		glm::mat4 projection_view;
		glm::mat4 inverse_projection_view;
	};

	struct ModelData {
		glm::mat4 model;
	};

	Renderer::Renderer(App::Window* window, API graphics_api, const App::StartupConfig& config) :
		pipe(std::make_shared<Render::Pipe>()),
		invoker(pipe->CreateInvoker()),
		executor_thread(
			[this, window, graphics_api, config](std::stop_token stop) {
				cancellation_token = stop;
				Render::Executor executor = pipe->CreateExecutor(window, graphics_api, config);
				while (!cancellation_token.stop_requested()) {
					executor.ExecuteCommands();
				}
			}
		) 
	{
		viewport_handle = invoker.CreateUniformBuffer(sizeof(ViewportData));
		lighting_handle = invoker.CreateUniformBuffer(sizeof(LightingData));
		camera_handle = invoker.CreateUniformBuffer(sizeof(CameraData));
		model_handle = invoker.CreateUniformBuffer(sizeof(ModelData));
	}

	const Invoker& Renderer::Command() const {
		return invoker;
	}

	void Renderer::UpdateViewportData(uint32_t width, uint32_t height) const {
		ViewportData viewport_data{
			.width = width,
			.height = height
		};

		ByteBox bytes =	ToBytes(std::make_unique<ViewportData>(std::move(viewport_data)));
		invoker.WriteUniformBuffer(viewport_handle, std::move(bytes));
	}

	void Renderer::UpdateLightingData() const {
		LightingData lighting_data{};

		ByteBox bytes =	ToBytes(std::make_unique<LightingData>(std::move(lighting_data)));
		invoker.WriteUniformBuffer(lighting_handle, std::move(bytes));
	}

	void Renderer::UpdateCameraData(const glm::mat4& view, const glm::mat4& projection) const {
		CameraData camera_data{
			.view = view,
			.projection = projection,
			.projection_view = projection * view,
			.inverse_projection_view = glm::inverse(projection * view)
		};

		ByteBox bytes =	ToBytes(std::make_unique<CameraData>(std::move(camera_data)));
		invoker.WriteUniformBuffer(camera_handle, std::move(bytes));
	}

	void Renderer::UpdateModelData(const glm::mat4& model) const {
		ModelData model_data{
			.model = model
		};

		ByteBox bytes =	ToBytes(std::make_unique<ModelData>(std::move(model_data)));
		invoker.WriteUniformBuffer(model_handle, std::move(bytes));
	}

	std::vector<ResourceBinding> Renderer::GetBindings() const {
		UniformBufferBinding viewport_binding{
			.binding_slot = VIEWPORT_BINDING_SLOT,
			.resource = viewport_handle
		};
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
		return { viewport_binding, lighting_binding, camera_binding, model_binding };
	}
}