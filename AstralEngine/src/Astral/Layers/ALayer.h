#pragma once
#include <Common.h>
#include "Astral/Events/EventListener.h"
#include "Astral/Window/FrameContext.h"

namespace Astral
{
	class ALayer : public EventListener
	{
	public:
		ALayer(const std::string name = "Layer") : debugName(name) {}

		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnImGuiRender() {}
		virtual void OnUpdate(const FrameContext& context) = 0;

		const std::string debugName;
	};
}
