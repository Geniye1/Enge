#include "ImGui3DViewport.h"

namespace Enge {

	ImGui3DViewport::ImGui3DViewport(unsigned int glfwTex)
		: m_renderTexture((ImTextureID)glfwTex)
	{
	}

	void ImGui3DViewport::OnUpdate() {
		if (show) {
			if (!Begin("Viewport")) {
				End();
			}
			else {
				ImGui::BeginChild("GameRender");
				ImVec2 wSize = ImGui::GetWindowSize();
				ImGui::Image(m_renderTexture, wSize, ImVec2(0, 1), ImVec2(1, 0));
				ImGui::EndChild();
				End();
			}
		}
	}

}