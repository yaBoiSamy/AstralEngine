#pragma once
#include "Astral/Layers/ALayer.h"
#include "Astral/Window/Window.h"
#include "Astral/Window/FrameContext.h"

namespace Astral
{
	class DebugLayer : public ALayer
	{
	public:
		DebugLayer(std::function<void()> renderImGuiWidgets);

		void OnUpdate(const FrameContext& context) override;

	private:
		void SetupDebugLayer();
		void RenderDebugLayer();

		const std::function<void()> renderImGuiWidgets;
	};
}