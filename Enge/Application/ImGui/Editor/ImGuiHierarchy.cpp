#include "ImGuiHierarchy.h"

namespace Enge {

	void ImGuiHierarchy::OnUpdate() {
		if (show) {
			if (Begin("Hierarchy")) {
				ImGui::Text("Hierarchy Hierarchy");
			}

			End();
		}
	}

}