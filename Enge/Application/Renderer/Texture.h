#pragma once

#include "../Enge_PCH.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../ThirdPartyHelpers/stb_image.h"

#include "../Shaders/Shader.h"

namespace Enge {
	
	class Texture {
	public:
		static bool LoadTexture(const char* texturePath, GLuint* GL_Texture, Shader* shader);
	};

}