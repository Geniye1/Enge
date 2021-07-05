#pragma once

#include "../Enge_PCH.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ImGuiEngeWindow.h"

namespace Enge {

	class ImGuiEditorManager {
	public:
		ImGuiEditorManager(GLFWwindow* window);
		~ImGuiEditorManager();

		void OnUpdate();
		void Render();

		bool IsHoveringOverTitleBar();

		void AddWindow(ImGuiEngeWindow* newWindow);
	private:
		std::vector<ImGuiEngeWindow*> m_Windows;

		void ShowDockSpace(bool* open);
		void SetStyle();
		void UpdateWindows();
		void DeleteWindows();
	};

}
