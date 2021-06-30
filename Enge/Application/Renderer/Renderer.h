#pragma once

#include "../Enge_PCH.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Shaders/Shader.h"
#include "../ThirdPartyHelpers/stb_image.h"

#include "../Application.h"
#include "../Input/Input.h"

namespace Enge {

	class Renderer {
	public:
		static void RendererInit(GLFWwindow& currentWindow);
	};

}