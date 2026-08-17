#pragma once
#include "Common.h"
#include "Astral/Rendering/Buffers/VertexArray.h"
#include "Astral/Rendering/Material/Material.h"

namespace Astral::Render {

	enum class Role {
		Invoker,
		Executor
	};

	struct CameraData {
		glm::mat4 view;
		glm::mat4 projection;
	};

	struct ModelData {
		glm::mat4 model;
	};


	struct NewFrameCommand {
		const CameraData cam_data;
		const uint32_t viewport_id;
		const uint32_t frame_width, frame_height;
		const glm::vec4 clear_color;
	};

	struct Draw3DCommand {
		const ModelData model_data;
		const IVertexArray* const mesh;
		const Material* const material;
	};

	using Command = std::variant<
		NewFrameCommand, 
		Draw3DCommand
	>;
}