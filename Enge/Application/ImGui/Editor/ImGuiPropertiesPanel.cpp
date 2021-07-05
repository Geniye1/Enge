#include "ImGuiPropertiesPanel.h"

namespace Enge {

	void ImGuiPropertiesPanel::OnUpdate() {
		if (show) {
			if (!Begin("Properties")) {
				End();
			}
			else {
				ImGui::Text("Is this shit working");
				ImGui::Button("Click me hoa yeah", ImVec2(150, 50));
				End();
			}
		}
	}

}