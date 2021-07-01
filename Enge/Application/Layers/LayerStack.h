#pragma once

#include "../Enge_PCH.h"

#include "Layer.h"

namespace Enge {

	class LayerStack {
	public:
		LayerStack() = default;
		~LayerStack();

		void PushLayer(Layer* layer);

		std::vector<Layer*>::iterator begin() { return m_layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_layers.end(); }

	private:
		std::vector<Layer*> m_layers;
	};

}