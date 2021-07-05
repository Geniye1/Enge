#pragma once

#include "../../Enge_PCH.h"

#include "../ImGuiEngeWindow.h"

namespace Enge {

	class ImGuiPropertiesPanel : public ImGuiEngeWindow {
	public:
		ImGuiPropertiesPanel() = default;
		~ImGuiPropertiesPanel() = default;

		virtual void OnUpdate() override;
	private:
		
	};

}