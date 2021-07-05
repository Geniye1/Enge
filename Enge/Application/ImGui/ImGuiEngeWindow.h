#pragma once

#include "../Enge_PCH.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace Enge {

	class ImGuiEngeWindow {
	public:
		ImGuiEngeWindow() = default;
		~ImGuiEngeWindow() = default;

		virtual void OnUpdate() {}
		void End();

		bool IsFocused();

		void Visibility(bool vis);
	protected:
		bool Begin(const char* name);

		bool show = true;
	};

}