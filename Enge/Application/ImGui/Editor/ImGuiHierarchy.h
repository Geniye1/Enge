#pragma once

#include "../../Enge_PCH.h"

#include "../ImGuiEngeWindow.h"

namespace Enge {

	class ImGuiHierarchy : public ImGuiEngeWindow {
	public:
		ImGuiHierarchy() = default;
		~ImGuiHierarchy() = default;

		virtual void OnUpdate() override;
	private:
	};

}