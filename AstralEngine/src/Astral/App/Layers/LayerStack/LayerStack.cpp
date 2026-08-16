#include <Common.h>
#include "LayerStack.h"
#include "Astral/App/Layers/Layer/Layer.h"

namespace Astral::App {

	using LayerVect = std::vector<Box<ALayer>>;

	LayerStack::LayerStack(Assets::AssetRegistry* assets) : boundary_index(0), assets(assets) {}

	LayerVect::iterator LayerStack::BoundaryIt() {
		AST_CORE_ASSERT(boundary_index <= layers.size(), "index out of bounds");
		return layers.begin() + boundary_index;
	}

	bool LayerStack::OnEvent(const Event& event) {
		return Broadcast(event);
	}

	ALayer* LayerStack::Find(std::string_view name) {
		for (const Box<ALayer>& layer : *this) {
			if (layer->name == name)
				return layer.get();
		}
		AST_CORE_WARN("Layer with name '{0}' not found", name);
		return nullptr;
	}


	void LayerStack::PushLayer(Box<ALayer> pushedLayer) {
		pushedLayer->SubscribeTo(*this);
		layers.insert(BoundaryIt(), std::move(pushedLayer));
		boundary_index++;
		(*LayerBack())->Attach(assets);
	}

	void LayerStack::PopLayer(LayerVect::iterator poppedLayer) {
		AST_CORE_ASSERT(LayerBegin() <= poppedLayer && poppedLayer < LayerEnd(), "Iterator out of layer range");
		(*poppedLayer)->UnsubscribeTo(*this);
		(*poppedLayer)->Detach();
		layers.erase(poppedLayer);
		boundary_index--;
	}

	void LayerStack::PushOverlay(Box<ALayer> pushedOverlay) {
		pushedOverlay->SubscribeTo(*this);
		layers.insert(layers.end(), std::move(pushedOverlay));
		(*OverlayBack())->Attach(assets);
	}

	void LayerStack::PopOverlay(LayerVect::iterator poppedOverlay) {
		AST_CORE_ASSERT(OverlayBegin() <= poppedOverlay && poppedOverlay < OverlayEnd(), "Iterator out of overlay range");
		(*poppedOverlay)->UnsubscribeTo(*this);
		(*poppedOverlay)->Detach();
		layers.erase(poppedOverlay);
	}

	void LayerStack::Update(const FrameContext& context) {
		for (auto& layer : layers) {
			layer->Update(context);
		}
	}

	void LayerStack::RenderImGuiWidgets() {
		for (auto& layer : layers) {
			layer->RenderUI();
		}
	}
}
