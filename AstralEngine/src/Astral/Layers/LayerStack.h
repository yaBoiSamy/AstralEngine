#pragma once
#include <Common.h>

#include "ALayer.h"

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

	LayerVect::const_iterator cbegin() const { return layers.cbegin(); }
	LayerVect::const_iterator cend()   const { return layers.cend(); }

	LayerVect::const_iterator cLayerBegin() const { return cbegin(); }
	LayerVect::const_iterator cLayerEnd() const { return BoundaryIt(); }

	LayerVect::const_iterator cOverlayBegin() const { return BoundaryIt(); }
	LayerVect::const_iterator cOverlayEnd() const { return cend(); }

private:
	LayerVect layers;
	size_t boundaryIndex;

	LayerVect::const_iterator BoundaryIt() const;
	LayerVect::iterator BoundaryIt();
};

