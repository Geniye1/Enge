#pragma once

#include "../../Enge_PCH.h"

#include "../ImGuiEngeWindow.h"

namespace Enge {

	class ImGuiFileExplorer : public ImGuiEngeWindow {
	public:
		ImGuiFileExplorer() = default;
		~ImGuiFileExplorer() = default;

		virtual void OnUpdate() override;
	private:
	};

}