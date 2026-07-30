#include "Common.h"
#include "Renderer.h"
#include "Astral/Rendering/RenderAPI/RenderAPI.h"
#include "Astral/Rendering/RenderCommand/RenderCommand.h"

namespace Astral {

	const glm::vec4 Renderer::CLEAR_COLOR = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
	std::optional<UniformBuffer<Renderer::CameraData>> Renderer::gpu_camera_data = std::nullopt;
	std::optional<UniformBuffer<Renderer::ModelData>> Renderer::gpu_model_data = std::nullopt;

	void Renderer::InitRenderer() {
		GfxAPI().Setup();
		RenderCommand::SetClearColor(CLEAR_COLOR);

		gpu_camera_data.emplace(UniformBuffer<Renderer::CameraData>(UsageHint::Dynamic, 0));
		gpu_model_data.emplace(UniformBuffer<Renderer::ModelData>(UsageHint::Dynamic, 1));
	}

	void Renderer::SetupFrame(std::pair<uint32_t, uint32_t> framebufferSize) {
		RenderCommand::SetActiveFrameBuffer(0);
		RenderCommand::SetViewport(framebufferSize);
		RenderCommand::Clear();
	}

	void Renderer::UpdateCameraData(CameraData& camdata) {
		AST_CORE_ASSERT(gpu_camera_data.has_value(), "Attempting to modify gpu data before Renderer initialization");
		gpu_camera_data->Write(camdata);
	}

	void Renderer::UpdateModelData(ModelData& modeldata) {
		AST_CORE_ASSERT(gpu_camera_data.has_value(), "Attempting to modify gpu data before Renderer initialization");
		gpu_model_data->Write(modeldata);
	}

	void Renderer::Submit(const IVertexArray& vertexArray, const Shader& shader) {
		shader.Bind();
		RenderCommand::Draw(vertexArray);
	}
}