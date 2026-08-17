#pragma once
#include "Common.h"
#include "Astral/Rendering/Command/CommandBuffer/CommandBuffer.h"
#include "Astral/Rendering/Buffers/VertexArray.h"
#include "Astral/Rendering/Material/Material.h"

namespace Astral::Render {

	class Invoker {
	public:
		Invoker(Arc<CommandBuffer> command_buffer);
		void NewFrame(CameraData cam_data, uint32_t viewport_id, uint32_t frame_width, uint32_t frame_height);
		void Draw3D(ModelData model_data, const IVertexArray* vertexArray, const Material* material);
		//void DrawBillboard(ModelData model_data, const Shader& shader, const Texture& texture);

	private:
		Arc<CommandBuffer> command_buffer;
	};

}
