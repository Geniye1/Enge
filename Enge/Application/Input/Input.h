#pragma once

#include "../Enge_PCH.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Enge {

	class Input {
	public:
		static void processInput(GLFWwindow* window);
	};

}