#pragma once

#include "Enge_PCH.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shaders/Shader.h"
#include "Renderer/Texture.h"
#include "Application.h"

namespace Enge {

	struct Transform {
		float x;
		float y;
		float z;
	};

	class Entity {
	public:
		Entity(const std::string& name, std::vector<float> vertices);

		virtual ~Entity() = default;

		virtual void OnStart() {}
		virtual void OnTick(float dt) {}
		virtual void OnEnd() {}

		void InitRender();
		void Render(glm::mat4 viewMatrix);
		void Render();

		const std::string& GetName() { return m_entityName; }
	public:
		std::string m_entityName;

		std::vector<float> m_vertices;

		bool isStatic = false;

		GLuint GL_VBO = 0;
		GLuint GL_VAO = 0;
		GLuint GL_IBO = 0;

		GLuint GL_Texture1 = 0;
		GLuint GL_Texture2 = 0;
		
		Transform transform = { 0.0f, 0.0f, 0.0f };
		glm::mat4 currentViewMatrix = glm::mat4(1.0f);

		Shader* currentShader = new Shader();
	};

}