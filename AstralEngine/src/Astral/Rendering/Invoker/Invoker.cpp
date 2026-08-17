#include "Common.h"
#include "Invoker.h"
#include "Astral/Rendering/Command/Command.h"
#include "Astral/Rendering/Command/CommandBuffer/CommandBuffer.h"
#include "Astral/Rendering/Buffers/VertexArray.h"
#include "Astral/Rendering/Material/Material.h"

namespace Astral::Render {

	Invoker::Invoker(Arc<CommandBuffer> command_buffer) : command_buffer(command_buffer) {}

	void Invoker::NewFrame(CameraData cam_data, uint32_t viewport_id,  uint32_t frame_width, uint32_t frame_height) {
		Command command = NewFrameCommand {
			.cam_data = cam_data,
			.viewport_id = viewport_id,
			.frame_width = frame_width,
			.frame_height = frame_height
		};

		command_buffer->InvokeCommand(std::move(command));
	}

	void Invoker::Draw3D(ModelData model_data, const IVertexArray* vertexArray, const Material* material) {
		Command command = Draw3DCommand {
			.model_data = model_data,
			.mesh = vertexArray,
			.material = material,
		};

		command_buffer->InvokeCommand(std::move(command));
	}
}