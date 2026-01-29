#pragma once
#include "Astral/Layers/ALayer.h"
#include "Astral/Window/Window.h"

namespace Astral
{
	class DebugLayer : public ALayer
	{
	public:
		DebugLayer(
			std::function<double()> getDeltaTime,
			std::function<Window::StateSnapshot()> getWindowState
		);
		~DebugLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;

	private:
		const std::function<double()> GetDeltaTime;
		const std::function<Window::StateSnapshot()> GetWindowState;
	};
}

