#pragma once

#include "../Enge_PCH.h"

namespace Enge {

	class Layer {

	public:
		Layer(const std::string& name = "DefaultLayerName");
		virtual ~Layer() = default;

		virtual void OnStart() {}
		virtual void OnEnd() {}
		virtual void OnUpdate(float dt) {}
		
		void enableLayer() { isEnabled = true; }
		void disableLayer() { isEnabled = false; }
		bool getLayerState() { return isEnabled; }

		const std::string& getName() const { return layerName; }

	protected:
		std::string layerName;

		bool isEnabled = true;
	};

}