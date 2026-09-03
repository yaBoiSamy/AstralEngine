#pragma once
#include "Astral/App/Layers/Layer/Layer.h"
#include "Astral/App/FrameContext.h"
#include "Astral/Assets/Shader/Shader.h"


namespace Astral::App {
	class Application;

	class DebugLayer : public ALayer {
	public:
		DebugLayer(Application* app, Render::Renderer* renderer);
		virtual void OnAttach() override;
		virtual void OnUpdate(const FrameContext& context) override;
		virtual void OnRenderUI() override;

		bool enable_yz = false;
		bool enable_xz = true;
		bool enable_xy = false;
	public:
		Render::Renderer* renderer;
		Render::ResourceHandle grid_enabler_handle;

		const uint32_t GRID_ENABLE_SLOT = 5;

	};
}

