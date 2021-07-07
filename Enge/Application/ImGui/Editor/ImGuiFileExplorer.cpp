#include "ImGuiFileExplorer.h"

namespace Enge {

	void ImGuiFileExplorer::OnUpdate() {
		if (show) {
			if (Begin("File Explorer")) {
				ImGui::Text("File Explorer ay ay ay ay");
			}

			End();
		}
	}

}