#pragma once
#include <Common.h>

namespace Astral
{
	struct FrameContext {
		struct InputSnapshot {
			const std::unordered_set<int> pressed_keys;
			const std::unordered_set<int> pressed_mouse_buttons;
			const double mouse_x;
			const double mouse_y;
		};

		struct WindowSnapshot {
			const std::string title;
			const int32_t x, y;     
			const uint32_t width, height;
			const uint32_t frame_width, frame_height;
			const bool focused;
			const bool vsync;
			const double deltatime;
		};

		const InputSnapshot input_snapshot;
		const WindowSnapshot window_snapshot;
	};
}
