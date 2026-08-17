#pragma once
#include "Astral/Rendering/Command/Command.h"
#include "Astral/Rendering/Command/CommandBuffer/CommandBuffer.h"


namespace Astral::Render {

	class Executor {
	public:
		Executor(Arc<CommandBuffer> command_buffer, std::function<void()> swap_frame_buffers);
		void ExecuteCommands();

	private:
		void NewFrame(NewFrameCommand command);
		void Draw3D(Draw3DCommand command);

		void OptimizeCommands();

		const uint32_t camera_data_binding_slot = 0;
		UniformBuffer<CameraData> gpu_camera_data;

		const uint32_t model_data_binding_slot = 1;
		UniformBuffer<ModelData> gpu_model_data;

		Arc<CommandBuffer> command_buffer;
		std::function<void()> swap_frame_buffers;
	};

}

