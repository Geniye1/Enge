#pragma once

#include "../Enge_PCH.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ImGuiEngeWindow.h"
#include "Editor/ImGui3DViewport.h"
#include "Editor/ImGuiPropertiesPanel.h"
#include "Editor/ImGuiHierarchy.h"
#include "Editor/ImGuiFileExplorer.h"

namespace Enge {

	class ImGuiEditorManager {
	public:
		ImGuiEditorManager() = default;
		~ImGuiEditorManager();

		void StartEditor(GLFWwindow* window, unsigned int frameBufferID);

		void OnUpdate();
		void Render();

		bool IsInteractingWithViewport();

		void AddWindow(ImGuiEngeWindow* newWindow);
	private:
		std::vector<ImGuiEngeWindow*> m_Windows;

		ImGui3DViewport* viewport = new ImGui3DViewport();
		ImGuiPropertiesPanel* properties = new ImGuiPropertiesPanel();
		ImGuiHierarchy* hierarchy = new ImGuiHierarchy();
		ImGuiFileExplorer* fileExplorer = new ImGuiFileExplorer();

		void ShowDockSpace(bool* open);
		void SetStyle();
		void UpdateWindows();
		void DeleteWindows();
	};

}
