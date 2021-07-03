#include "ImGuiWindow.h"

namespace Enge {

	bool ImGuiWindow::Begin(const char* name) {
		return ImGui::Begin(name, &show);
	}
	
	void ImGuiWindow::End() {
		ImGui::End();
	}

	void ImGuiWindow::Visibility(bool vis) {
		show = vis;
	}
}