#include "Common.h"
#include "CommandBuffer.h"

namespace Astral::Render {

	CommandBuffer::CommandBuffer() :
		frame_ready(false),
		frame_rendered(false),
		inactive_commands(&commands1),
		processed_commands(&commands2) {}

	void CommandBuffer::InvokeCommand(Command command) {
		inactive_commands->push_back(std::move(command));
	}

	std::vector<Command>& CommandBuffer::ProcessedCommands() {
		return *processed_commands;
	}

	void CommandBuffer::SwapBuffer(Role role) {
		std::unique_lock lock(mutex);

		switch (role) {
		case Role::Invoker:
			frame_ready = true;
			if (!frame_rendered) {
				// gpu bottlenecking
				buffer_swap_signal.wait(lock, [this] { return frame_rendered; });
				return;
			}
			break;
		case Role::Executor:
			frame_rendered = true;
			if (!frame_ready) {
				// cpu bottlenecking
				buffer_swap_signal.wait(lock, [this] { return frame_ready; });
				return;
			}
			break;
		}

		if (inactive_commands == &commands1) {
			inactive_commands = &commands2;
			processed_commands = &commands1;
		}
		else {
			inactive_commands = &commands1;
			processed_commands = &commands2;
		}

		buffer_swap_signal.notify_one();

		frame_ready = false;
		frame_rendered = false;
	}
}