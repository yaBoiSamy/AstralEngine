#pragma once
#include <Common.h>
#include "Astral/App/Events/EventHandlers/EventHandlers.h"
#include "Astral/App/FrameContext.h"
#include "Astral/Assets/AssetRegistry/AssetRegistry.h"


namespace Astral::App {

	class Application;

	class ALayer : public EventListener, public EventBroadcaster
	{
	public:
		ALayer(Application* app, const std::string name);

		void Attach(Assets::AssetRegistry* assets);
		void Detach();
		void Update(const FrameContext& context);
		void RenderUI();
		Assets::AssetRegistry& Assets();
		Application& App();

		const std::string name;

	protected:
		virtual bool OnEvent(const Event& event) override;
		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnRenderUI();
		virtual void OnUpdate(const FrameContext& context);

	private:
		Application* app;
		Assets::AssetRegistry* assets;
	};
}
