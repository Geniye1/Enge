#include "ImGui3DViewport.h"

namespace Enge {

	/*ImGui3DViewport::ImGui3DViewport(unsigned int glfwTex)
		: m_renderTexture((ImTextureID)glfwTex)
	{
	}*/

	void ImGui3DViewport::Start(unsigned int glfwTex) {
		m_renderTexture = (ImTextureID)glfwTex;
	}

	void ImGui3DViewport::OnUpdate() {
		if (show) {
			if (!Begin("Viewport")) {
				End();
			}
			else {
				ImGui::BeginChild("GameRender");
				ImVec2 wSize = ImGui::GetWindowViewport()->Size;
				ImDrawList* d = ImGui::GetWindowDrawList();
				ImGui::InvisibleButton("ViewportInteract", wSize);
				
				if (ImGui::IsItemActive()) {
					isInteractingWithViewport = true;
				}
				else {
					isInteractingWithViewport = false;
				}

				/* 
					This clusterfuck is meant to preserve the 16:9 aspect ratio whenever the viewport is resized,
					of course it doesn't EXACTLY equal 16:9 but it seems to look alright so imma just take what I
					can get I solved this at 3AM 3 fucking AM just want it to be known 
				*/
				ImVec2 wMin = ImGui::GetWindowContentRegionMin();
				ImVec2 wMax = ImGui::GetWindowContentRegionMax();

				wMin.x += ImGui::GetWindowPos().x;
				wMin.y += ImGui::GetWindowPos().y;
				wMax.x += ImGui::GetWindowPos().x;
				wMax.y += ImGui::GetWindowPos().y;
				
				float distanceBtwMinAndMaxY = wMax.y - wMin.y;
				float distanceBtwMinAndMaxX = wMax.x - wMin.x;
				if (distanceBtwMinAndMaxY < 1080) {
					float offsetY = (1080 - distanceBtwMinAndMaxY) / 2;
					float offsetX = ((1920 - distanceBtwMinAndMaxX) / 2) - (1080 - distanceBtwMinAndMaxY); // I have no idea why this works but shit ill take it
					wMin.y += offsetY;
					wMin.x -= offsetX;
					wMax.y -= offsetY;
					wMax.x += offsetX;
				}
				else if (distanceBtwMinAndMaxY > 1080) {
					float offsetY = (distanceBtwMinAndMaxY - 1080) / 2;
					wMin.y += offsetY;
					wMax.y -= offsetY;
				}
				
				d->AddImage(m_renderTexture, wMin, wMax, ImVec2(0, 1), ImVec2(1, 0));

				//ImGui::Image(m_renderTexture, wSize, ImVec2(0, 1), ImVec2(1, 0));
				ImGui::EndChild();
				End();
			}
		}
	}

	bool ImGui3DViewport::IsInteractingWithViewport() {
		return isInteractingWithViewport;
	}

}