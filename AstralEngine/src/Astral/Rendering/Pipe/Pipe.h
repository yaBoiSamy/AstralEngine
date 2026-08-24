#pragma once
#include "Invoker/Invoker.h"
#include "Executor/Executor.h"
#include "Command/CommandBuffer/CommandBuffer.h"
#include "ResourceRegistry/ResourceRegistry.h"


namespace Astral::Render {
	class Pipe {
	public:
		Pipe();
		Invoker CreateInvoker();
		Executor CreateExecutor(App::Window* window, API graphics_api);

	private:
		CommandBuffer commands;
		ResourceRegistry registry;
	};
}

