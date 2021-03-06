#include "PerspectiveCameraController.h"

namespace Enge {

	PerspectiveCameraController::PerspectiveCameraController(GLFWwindow* window)
		: m_window(window)
	{	
	}
	
	glm::mat4 PerspectiveCameraController::updateCameraPosition(float dt) {

		if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS) {
			m_camera.MoveForward(dt);
		}
		if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS) {
			m_camera.MoveBackward(dt);
		}
		if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS) {
			m_camera.MoveLeft(dt);
		}
		if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS) {
			m_camera.MoveRight(dt);
		}
		if (glfwGetKey(m_window, GLFW_KEY_Q) == GLFW_PRESS) {
			m_camera.MoveUp(dt);
		}
		if (glfwGetKey(m_window, GLFW_KEY_E) == GLFW_PRESS) {
			m_camera.MoveDown(dt);
		}

		if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			m_camera.StartSprinting();
		}
		else {
			m_camera.StopSprinting();
		}
	
		return m_camera.GetLookAt();
	}

	void PerspectiveCameraController::updateMouseLook() {
		glfwGetCursorPos(m_window, &xPos, &yPos);
		
		if (firstMouse) {
			lastX = xPos;
			lastY = yPos;
			firstMouse = false;
		}

		double xOffset = xPos - lastX;
		double yOffset = lastY - yPos;
		lastX = xPos;
		lastY = yPos;

		xOffset *= mouseSensitivity;
		yOffset *= mouseSensitivity;

		yaw += xOffset;
		pitch += yOffset;

		if (pitch > 89.9f) {
			pitch = 89.0f;
		} 
		else if (pitch < -89.9f) {
			pitch = -89.0f;
		}

		glm::vec3 mouseDirection;
		mouseDirection.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		mouseDirection.y = sin(glm::radians(pitch));
		mouseDirection.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		m_camera.m_cameraFront = glm::normalize(mouseDirection);
	}

	// This will set to true from the Editor layer whenever the mouse is clicked out of the window
	// so as to stop the camera from jumping 
	void PerspectiveCameraController::IsFirstMouse() {
		firstMouse = true;
	}

}
