#include "Input.h"

namespace Enge {

	void Input::processInput(GLFWwindow* window) {

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}

	}

	bool Input::GetMouseButtonDown(int mouseCode) {
		if (glfwGetMouseButton(glfwGetCurrentContext(), mouseCode) == GLFW_PRESS) 
			return true;

		return false;
	}

}
