#include "Application.h"

#include "Renderer/Renderer.h"

namespace Enge {

	Application* Application::s_AppInstance = nullptr;

	int Application::ApplicationInit() {
		
		LOG_START();

		// Singleton pattern
		assert(!s_AppInstance, LOG_ERR("ERROR::APPLICATION::DUMBASS::APPLICATION_ALREADY_RUNNING\n"));
		s_AppInstance = this;
		shouldClose = false;

		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		LOG(ENGE_INFO, "STARTING CORE GLFW V%s\n\n", glfwGetVersionString());

		Application::window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Enge", NULL, NULL);
		if (window == NULL) {
			LOG_ERR("ERROR::GLFW_WINDOW::FAILED_TO_CREATE_WINDOW_LMAO\n");
			glfwTerminate();
			return EXIT_FAILURE;
		}
		glfwMakeContextCurrent(window);

		LOG(ENGE_INFO, "GLFW WINDOW SUCCESSFULLY CREATED...\n");

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			LOG_ERR("ERROR:::GLAD::FAILED_TO_INIT_GLAD_MAN_YOURE_FUCKED_BRO\n");
			glfwTerminate();
			return EXIT_FAILURE;
		}

		LOG(ENGE_INFO, "GLAD SUCCESSFULLY LOADED...\n");

		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT); 
		glEnable(GL_DEPTH_TEST);

		glfwSetFramebufferSizeCallback(window, Application::ApplicationResizeCallback); 
		glfwSetErrorCallback(Application::ApplicationErrorCallback);

		Renderer::RendererInit(*window);
		// Initalize Engine input class n shit

		return EXIT_SUCCESS;
	}

	void Application::ApplicationRun() {
		while (glfwWindowShouldClose(Application::window)) {
			// process input
			// call the renderer
		}
	}

	void Application::ApplicationEnd() {
		shouldClose = true;
		glfwTerminate();
	}

	void Application::ApplicationErrorCallback(int error, const char* description) {
		LOG_ERR("GLFW ERROR: code %i, msg: %s\n", error, description);
	}

	void Application::ApplicationResizeCallback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}

	void Application::ApplicationWindowCloseCallback(void) {
		Application::s_AppInstance->ApplicationEnd();
	}
}