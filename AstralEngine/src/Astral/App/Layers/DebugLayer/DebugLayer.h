#pragma once
#include "Astral/App/Layers/Layer/Layer.h"
#include "Astral/App/FrameContext.h"
#include "Astral/Rendering/Renderer/Renderer.h"

namespace Astral::App {

	class DebugLayer : public ALayer
	{
	public:
		DebugLayer(Render::Renderer* renderer, std::function<void()> renderImGuiWidgets);

		void OnUpdate(const FrameContext& context) override;

	private:
		void SetupDebugLayer(const FrameContext& context);
		void RenderDebugLayer();

		const std::function<void()> renderImGuiWidgets;
		Render::Renderer* renderer;
	};
}