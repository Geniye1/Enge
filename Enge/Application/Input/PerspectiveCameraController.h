#pragma once

#include "../Enge_PCH.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Application.h"
#include "../Input/Camera.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Enge {
	class PerspectiveCameraController
	{
	public:
		PerspectiveCameraController(GLFWwindow* window);

		glm::mat4 updateCameraPosition(float dt);
		void updateMouseLook();
		void IsFirstMouse();

	private:
		GLFWwindow* m_window;

		Camera m_camera;

		// Constants
		const float mouseSensitivity = 0.1f;

		// Collecting mouse information
		double xPos = 0;
		double yPos = 0;

		double lastX = WINDOW_WIDTH / 2;
		double lastY = WINDOW_HEIGHT / 2;

		// Mouse variables
		double yaw = -90.0f;
		double pitch = 0;

		bool firstMouse = true;
	};
}


