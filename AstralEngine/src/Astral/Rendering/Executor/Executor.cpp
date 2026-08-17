#include "Common.h"
#include "Executor.h"
#include "Astral/Rendering/Command/Command.h"
#include "Astral/Rendering/Command/CommandBuffer/CommandBuffer.h"
#include "Astral/Rendering/GraphicsAPI/GraphicsAPI.h"


namespace Astral::Render {
	Executor::Executor(Arc<CommandBuffer> command_buffer, std::function<void()> swap_frame_buffers) :
		command_buffer(command_buffer),
		swap_frame_buffers(swap_frame_buffers),
		gpu_camera_data(UsageHint::Dynamic, camera_data_binding_slot), 
		gpu_model_data(UsageHint::Dynamic, model_data_binding_slot)
	{
		GfxAPI().Setup();
	}

	void Executor::ExecuteCommands() {
		OptimizeCommands();
		for (Command& command : command_buffer->ProcessedCommands()) {
			std::visit(overloaded{
				[&](const NewFrameCommand& command) {
					NewFrame(command);
				},
				[&](const Draw3DCommand& command) {
					Draw3D(command);
				}
			}, command);
		}
		swap_frame_buffers();
		command_buffer->ProcessedCommands().clear();
		command_buffer->SwapBuffer(Role::Executor);
	}

	void Executor::NewFrame(NewFrameCommand command) {
		GfxAPI().SetActiveFrameBuffer(command.viewport_id);
		GfxAPI().SetViewport(command.frame_width, command.frame_height);
		GfxAPI().Clear(command.clear_color);
	}

	void Executor::Draw3D(Draw3DCommand command) {
		gpu_model_data.Write(command.model_data);
		command.material->Bind();
		GfxAPI().Draw(*command.mesh);
	}

	void Executor::OptimizeCommands() {

	}


}
