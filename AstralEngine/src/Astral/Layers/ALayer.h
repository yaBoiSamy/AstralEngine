#pragma once
#include <Common.h>
#include "Astral/Events/EventListener.h"

namespace Astral
{
	class ALayer : public EventListener
	{
	public:
		ALayer(const std::string name = "Layer") : debugName(name) {}

		virtual void OnAttach() = 0;
		virtual void OnDetach() = 0;
		virtual void OnUpdate() = 0;

		const std::string debugName;
	};
}


