#include "ImGuiEngeWindow.h"

namespace Enge {

	bool ImGuiEngeWindow::Begin(const char* name, ImGuiWindowFlags flags) {
		return ImGui::Begin(name, &show, flags);
	}
	
	void ImGuiEngeWindow::End() {
		ImGui::End();
	}

	bool ImGuiEngeWindow::IsFocused() {
		return ImGui::IsAnyItemHovered();
	}

	void ImGuiEngeWindow::Visibility(bool vis) {
		show = vis;
	}
}