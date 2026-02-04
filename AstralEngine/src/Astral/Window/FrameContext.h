#pragma once
#include <Common.h>

namespace Astral
{
	struct FrameContext {
		struct InputSnapshot {
			const std::unordered_set<int> pressedKeys;
			const std::unordered_set<int> pressedMouseButtons;
			const double mouseX;
			const double mouseY;
		};

		struct WindowSnapshot {
			const std::string title;
			const uint32_t x;
			const uint32_t y;
			const uint32_t width;
			const uint32_t height;        
			const uint32_t framebufferSizeX;
			const uint32_t framebufferSizeY;
			const bool focused;
			const bool vSync;
		};

		const InputSnapshot inputSnapshot;
		const WindowSnapshot windowSnapshot;
		const double deltaTime;
	};
}
