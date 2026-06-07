#pragma once
#include "Astral/Window/Window.h"

namespace Astral
{
	class RenderOrchestrator
	{
	public:
		RenderOrchestrator() = default;
		void SetupFrame(std::pair<uint32_t, uint32_t> framebufferSize);
		void PresentFrame(Window& window);
	};
}

