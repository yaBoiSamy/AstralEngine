#pragma once
#include <Common.h>
#include "Astral/Events/EventHandlers/EventHandlers.h"
#include "Astral/Window/FrameContext.h"


namespace Astral
{
	class ALayer : public EventListener, public EventBroadcaster
	{
	public:
		ALayer(const std::string name = "Layer") : name(name) {}

		virtual bool OnEvent(const Event& event) override { return Broadcast(event); }
		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnImGuiRender() {}
		virtual void OnUpdate(const FrameContext& context) = 0;

		const std::string name;
	};
}
