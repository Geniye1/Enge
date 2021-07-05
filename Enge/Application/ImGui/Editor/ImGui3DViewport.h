#pragma once

#include "../../Enge_PCH.h"

#include "../ImGuiEngeWindow.h"

namespace Enge {

	class ImGui3DViewport : public ImGuiEngeWindow {
	public:
		ImGui3DViewport() = default;
		~ImGui3DViewport() = default;

		void Start(unsigned int glfwTex);
		bool IsInteractingWithViewport();

		virtual void OnUpdate() override;
	private:
		const float viewportWidthRatioX = 16;
		const float viewportWidthRatioY = 9;

		ImTextureID m_renderTexture = 0;

		bool isInteractingWithViewport = false;
	};

}