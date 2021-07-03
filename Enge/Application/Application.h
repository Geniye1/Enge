#pragma once

#include "Enge_PCH.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <assert.h>

#include "Layers/LayerStack.h"

#define WINDOW_WIDTH  1080
#define WINDOW_HEIGHT 720

namespace Enge {
	
	class Application {
	public:
		Application() = default;

		int ApplicationInit();
		void ApplicationRun();
		void ApplicationEnd();

		static void ApplicationErrorCallback(int error, const char* description);
		static void ApplicationResizeCallback(GLFWwindow* window, int width, int height);
		static void ApplicationWindowCloseCallback(void);

		static Application* s_AppInstance;
	private:
		GLFWwindow* window;

		LayerStack m_layerStack;

		bool shouldClose = false;

		double deltaTime = 0.0f;
		double lastFrame = 0.0f;
	};

}