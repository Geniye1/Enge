#pragma once

#include "../Enge_PCH.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../ThirdPartyHelpers/stb_image.h"

#include "../Layers/Layer.h"
#include "../Shaders/Shader.h"
#include "../Application.h"

namespace Enge {

	class TestLayer : public Layer {
	public:
		TestLayer();
		virtual ~TestLayer() = default;

		virtual void OnStart() override;
		virtual void OnEnd() override;
		virtual void OnUpdate() override;

	private:
		std::vector<float> vertices;

		GLuint GL_VBO = 0;
		GLuint GL_VAO = 0;
		GLuint GL_IBO = 0;

		GLuint GL_Texture1 = 0;
		GLuint GL_Texture2 = 0;
		
		Shader* currentShader = new Shader();
	};

}