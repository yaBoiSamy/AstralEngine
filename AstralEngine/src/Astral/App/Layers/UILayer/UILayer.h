#pragma once
#include "Astral/App/Layers/Layer/Layer.h"
#include "Astral/App/FrameContext.h"
#include "Astral/Rendering/Renderer/Renderer.h"

namespace Astral::App {
	class Application;

	class UILayer : public ALayer
	{
	public:
		UILayer(Application* app, Render::Renderer* renderer, std::function<void()> renderImGuiWidgets);

		void OnUpdate(const FrameContext& context) override;
		virtual bool OnMouseButtonPressedEvent(const Astral::App::MouseButtonPressedEvent& event) override;

	private:
		void SetupDebugLayer(const FrameContext& context);
		void RenderDebugLayer();

		const std::function<void()> renderImGuiWidgets;
		Render::Renderer* renderer;
	};
}