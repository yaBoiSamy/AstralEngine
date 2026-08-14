#include <Common.h>
#include "LayerStack.h"
#include "Astral/Model/Layers/ALayer.h"

namespace Astral
{
	using LayerVect = std::vector<Box<ALayer>>;

	LayerStack::LayerStack() : boundary_index(0) {}

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
		(*LayerBack())->OnAttach();
	}

	void LayerStack::PopLayer(LayerVect::iterator poppedLayer) {
		AST_CORE_ASSERT(LayerBegin() <= poppedLayer && poppedLayer < LayerEnd(), "Iterator out of layer range");
		(*poppedLayer)->UnsubscribeTo(*this);
		(*poppedLayer)->OnDetach();
		layers.erase(poppedLayer);
		boundary_index--;
	}

	void LayerStack::PushOverlay(Box<ALayer> pushedOverlay) {
		pushedOverlay->SubscribeTo(*this);
		layers.insert(layers.end(), std::move(pushedOverlay));
		(*OverlayBack())->OnAttach();
	}

	void LayerStack::PopOverlay(LayerVect::iterator poppedOverlay) {
		AST_CORE_ASSERT(OverlayBegin() <= poppedOverlay && poppedOverlay < OverlayEnd(), "Iterator out of overlay range");
		(*poppedOverlay)->UnsubscribeTo(*this);
		(*poppedOverlay)->OnDetach();
		layers.erase(poppedOverlay);
	}

	void LayerStack::Update(const FrameContext& context) {
		for (auto& layer : layers) {
			layer->OnUpdate(context);
		}
	}

	void LayerStack::RenderImGuiWidgets() {
		for (auto& layer : layers) {
			layer->OnImGuiRender();
		}
	}
}
