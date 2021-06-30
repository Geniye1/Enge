#pragma once

#include "Enge_PCH.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <assert.h>

#define WINDOW_WIDTH  1280
#define WINDOW_HEIGHT 720

namespace Enge {
	
	class Application {
	public:
		int ApplicationInit();
		void ApplicationRun();
		void ApplicationEnd();

		static void ApplicationErrorCallback(int error, const char* description);
		static void ApplicationResizeCallback(GLFWwindow* window, int width, int height);
		static void ApplicationWindowCloseCallback(void);

		static Application* s_AppInstance;
	private:
		GLFWwindow* window;

		bool shouldClose;
	};

}