#pragma once
#include "Astral/Rendering/Buffers/VertexArray.h"
#include <glm/glm.hpp>

namespace Astral {

	class Renderer {
	public:
		static void InitRenderer();

		static void SetupFrame(std::pair<uint32_t, uint32_t> framebufferSize);

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