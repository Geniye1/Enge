#pragma once

#include "../../Enge_PCH.h"

#include "../ImGuiEngeWindow.h"

namespace Enge {

	class ImGui3DViewport : public ImGuiEngeWindow {
	public:
		ImGui3DViewport(unsigned int glfwTex);
		~ImGui3DViewport() = default;

		virtual void OnUpdate() override;
	private:
		ImTextureID m_renderTexture = 0;
	};

}