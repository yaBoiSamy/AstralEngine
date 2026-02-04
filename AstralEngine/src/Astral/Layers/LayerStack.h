#pragma once
#include <Common.h>
#include "Astral/Layers/ALayer.h"
#include "Astral/Window/FrameContext.h"


namespace Astral
{
	/*
	Invariant:
	[0, boundaryIndex) => layers
	[boundaryIndex, layers.size()) => overlays
	*/
	class LayerStack
	{
		using LayerVect = std::vector<ptr<ALayer>>;
	public:
		LayerStack();

		void PushLayer(ptr<ALayer> layer);
		void PopLayer(LayerVect::const_iterator layer);
		void PushOverlay(ptr<ALayer> overlay);
		void PopOverlay(LayerVect::const_iterator overlay);

		void Update(const FrameContext& context);
		void RenderImGuiWidgets();

		LayerVect::const_iterator cbegin() const { return layers.cbegin(); }
		LayerVect::const_iterator cend()   const { return layers.cend(); }

		LayerVect::const_iterator cLayerBegin() const { return cbegin(); }
		LayerVect::const_iterator cLayerEnd() const { return BoundaryIt(); }

		LayerVect::const_iterator cOverlayBegin() const { return BoundaryIt(); }
		LayerVect::const_iterator cOverlayEnd() const { return cend(); }

		template<EventType EventT>
		bool PropagateEvent(const EventT& event) {
			for (auto it = cbegin(); it != cend(); ++it) {
				if (event.Dispatch(**it)) {
					return true;
				}
			}
			return false;
		}

	private:
		LayerVect layers;
		size_t boundaryIndex;

		LayerVect::const_iterator BoundaryIt() const;
		LayerVect::iterator BoundaryIt();
	};

}
