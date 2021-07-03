#pragma once

#include "../../Enge_PCH.h"

#include "../ImGuiWindow.h"

namespace Enge {

	class ImGui3DViewport : public ImGuiWindow {
	public:
		ImGui3DViewport(unsigned int glfwTex);
		~ImGui3DViewport() = default;

		virtual void OnUpdate() override;
	private:
		ImTextureID m_renderTexture = 0;
	};

}