#pragma once
#include "Astral/App/Layers/Layer/Layer.h"
#include "Astral/App/Window/Window.h"
#include "Astral/App/FrameContext.h"

namespace Astral::App {

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