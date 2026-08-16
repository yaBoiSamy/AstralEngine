#pragma once
#include <Common.h>
#include "Astral/App/Layers/Layer/Layer.h"
#include "Astral/App/FrameContext.h"
#include "Astral/Assets/AssetRegistry.h"


namespace Astral::App {

	/*
	Invariant:
	[0, boundary_index) => layers
	[boundary_index, layers.size()) => overlays
	*/
	class LayerStack : public EventListener, public EventBroadcaster
	{
		using LayerVect = std::vector<Box<ALayer>>;
	public:
		LayerStack(Assets::AssetRegistry* assets);

		virtual bool OnEvent(const Event& event) override;

		ALayer* Find(std::string_view name);

		void PushLayer(Box<ALayer> layer);
		void PopLayer(LayerVect::iterator layer);
		void PushOverlay(Box<ALayer> overlay);
		void PopOverlay(LayerVect::iterator overlay);

		void Update(const FrameContext& context);
		void RenderImGuiWidgets();

		LayerVect::iterator begin() { return layers.begin(); }
		LayerVect::iterator end() { return layers.end(); }

		LayerVect::iterator LayerBegin() { return layers.begin(); }
		LayerVect::iterator LayerBack() { return --BoundaryIt(); }
		LayerVect::iterator LayerEnd() { return BoundaryIt(); }

		LayerVect::iterator OverlayBegin() { return BoundaryIt(); }
		LayerVect::iterator OverlayBack() { return --layers.end(); }
		LayerVect::iterator OverlayEnd() { return layers.end(); }

	private:
		LayerVect layers;
		size_t boundary_index;
		Assets::AssetRegistry* assets;

		LayerVect::iterator BoundaryIt();
	};

}
