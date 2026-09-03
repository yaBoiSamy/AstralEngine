#pragma once
#include <vector>
#include <mutex>
#include "Astral/Rendering/Pipe/Command/Command.h"


namespace Astral::Render {

	class CommandBuffer {
	public:
		CommandBuffer();
		void InvokeCommand(Command command);
		std::vector<Command>& ProcessedCommands();
		void SwapBuffer(Role role);

	private:
		std::mutex mutex;
		std::condition_variable_any buffer_swap_signal;
		uint32_t frame_generation;
		bool frame_ready;
		bool frame_rendered;
		std::vector<Command>* inactive_commands;
		std::vector<Command>* processed_commands;

		std::vector<Command> commands1;
		std::vector<Command> commands2;
	};

}
