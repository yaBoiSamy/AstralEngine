#include "Common.h"
#include "LayerStack.h"

namespace Astral
{
	using LayerVect = std::vector<ptr<ALayer>>;

	LayerStack::LayerStack() : boundaryIndex(0) {}

	LayerVect::const_iterator LayerStack::BoundaryIt() const {
		AST_CORE_ASSERT(boundaryIndex <= layers.size(), "index out of bounds");
		return layers.cbegin() + boundaryIndex;
	}

	LayerVect::iterator LayerStack::BoundaryIt() {
		AST_CORE_ASSERT(boundaryIndex <= layers.size(), "index out of bounds");
		return layers.begin() + boundaryIndex;
	}

	void LayerStack::PushLayer(ptr<ALayer> pushedLayer) {
		layers.insert(BoundaryIt(), std::move(pushedLayer));
		boundaryIndex++;
	}

	void LayerStack::PopLayer(LayerVect::const_iterator poppedLayer) {
		AST_CORE_ASSERT(cLayerBegin() <= poppedLayer && poppedLayer < cLayerEnd(), "Iterator out of layer range");
		layers.erase(poppedLayer);
		boundaryIndex--;
	}

	void LayerStack::PushOverlay(ptr<ALayer> pushedOverlay) {
		layers.insert(layers.end(), std::move(pushedOverlay));
	}

	void LayerStack::PopOverlay(LayerVect::const_iterator poppedOverlay) {
		AST_CORE_ASSERT(cOverlayBegin() <= poppedOverlay && poppedOverlay < cOverlayEnd(), "Iterator out of overlay range");
		layers.erase(poppedOverlay);
	}

	void LayerStack::Update() {
		for (auto& layer : layers) {
			layer->OnUpdate();
		}
	}
}
