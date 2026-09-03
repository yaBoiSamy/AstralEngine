#include "Common.h"
#include "Layer.h"
#include "Astral/App/Application/Application.h"


namespace Astral::App {

	ALayer::ALayer(Application* app, const std::string name) : app(app), name(name) {}

	void ALayer::Attach(Assets::AssetRegistry* assets) {
		this->assets = assets;
		OnAttach();
	}

	void ALayer::Detach() {
		OnDetach();
		assets = nullptr;
	}

	void ALayer::Update(const FrameContext& context) {
		OnUpdate(context);
	}

	void ALayer::RenderUI() {
		OnRenderUI();
	}

	Assets::AssetRegistry& ALayer::Assets() {
		AST_CORE_ASSERT(assets, "Accessing assets of a detached layer");
		return *assets;
	}

	Application& ALayer::App() {
		return *app;
	}


	// Default impls
	bool ALayer::OnEvent(const Event& event) { return Broadcast(event); }
	void ALayer::OnAttach() {};
	void ALayer::OnDetach() {};
	void ALayer::OnRenderUI() {}
	void ALayer::OnUpdate(const FrameContext& context) {}

}