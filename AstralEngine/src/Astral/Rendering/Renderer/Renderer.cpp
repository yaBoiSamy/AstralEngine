#include "Common.h"
#include "Renderer.h"
#include "Astral/Rendering/RenderAPI/RenderAPI.h"
#include "Astral/Rendering/RenderCommand/RenderCommand.h"
#include "Astral/Rendering/Shader/Shader.h"
#include "Astral/Rendering/Buffers/Buffers.h"
#include "Astral/Rendering/Buffers/VertexArray.h"

namespace Astral::Render {

	const glm::vec4 Renderer::CLEAR_COLOR = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
	std::optional<UniformBuffer<Renderer::CameraData>> Renderer::gpu_camera_data = std::nullopt;
	std::optional<UniformBuffer<Renderer::ModelData>> Renderer::gpu_model_data = std::nullopt;

	void Renderer::InitRenderer() {
		GfxAPI().Setup();
		RenderCommand::SetClearColor(CLEAR_COLOR);

		gpu_camera_data.emplace(UniformBuffer<Renderer::CameraData>(UsageHint::Dynamic, 0));
		gpu_model_data.emplace(UniformBuffer<Renderer::ModelData>(UsageHint::Dynamic, 1));
	}

	void Renderer::SetupFrame(uint32_t frame_width, uint32_t frame_height) {
		RenderCommand::SetActiveFrameBuffer(0);
		RenderCommand::SetViewport(frame_width, frame_height);
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

	void Renderer::Submit(const IVertexArray& vertexArray) {
		RenderCommand::Draw(vertexArray);
	}
}