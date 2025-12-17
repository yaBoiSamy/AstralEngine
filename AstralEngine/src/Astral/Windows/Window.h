#pragma once

#include <Common.h>
#include <Astral/Events/Event.h>

#include "Astral/Core.h"

namespace Astral {
	using EventCallbackFn = std::function<void(Event&)>;

	struct Window {
		const std::string title;
		const uint32_t width, height;

		Window(std::string title = "Astral", uint32_t width = 1080, uint32_t height = 1920) :
			title(title),
			width(width),
			height(height) {}
	};


	Window Update(Window win);

	Window SetCallback(EventCallbackFn callback);
}
