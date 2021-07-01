#include "LayerStack.h"

namespace Enge {

	LayerStack::~LayerStack() {
		for (Layer* layer : m_layers) {
			layer->OnEnd();
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer) {
		m_layers.emplace(m_layers.begin(), layer);
		layer->OnStart();
	}
}