#pragma once
#include "Common.h"
#include "Astral/Rendering/Buffers/VertexArray.h"
#include "Astral/Rendering/shader/Shader.h"
#include "Astral/Rendering/Buffers/Buffers.h"

namespace Astral::Render {

	class Renderer {
	public:
		static void InitRenderer();

		static void SetupFrame(uint32_t frame_width, uint32_t frame_height);

		static void Submit(const IVertexArray& vertexArray);

	private:
		static const glm::vec4 CLEAR_COLOR;

	public:
		// UNIFORMS ARE MANAGED HERE

		struct CameraData {
			glm::mat4 view;
			glm::mat4 projection;
		};
		static void UpdateCameraData(CameraData& camdata);

		struct ModelData {
			glm::mat4 model;
		};
		static void UpdateModelData(ModelData& modeldata);

	private:
		static std::optional<UniformBuffer<CameraData>> gpu_camera_data;
		static std::optional<UniformBuffer<ModelData>> gpu_model_data;
	};

}