#include "Entity.h"

namespace Enge {

	Entity::Entity(const std::string& name, std::vector<float> vertices)
		: m_entityName(name), m_vertices(vertices)
	{
	}

	void Entity::InitRender() {
		glGenVertexArrays(1, &GL_VAO);
		glBindVertexArray(GL_VAO);

		glGenBuffers(1, &GL_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, GL_VBO);
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), &m_vertices.front(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);

		currentShader->loadShaderProgram("Application/Shaders/Base Shaders/BaseVertexShader.glsl", "Application/Shaders/Base Shaders/BaseFragmentShader.glsl");
		
		bool textureLoadSuccess = Texture::LoadTexture("Application/Rsc/rocks.jpg", &GL_Texture1, currentShader);
		if (!textureLoadSuccess) {
			LOG_ERR("ERROR::TEXTURE::TEXTURE_COULD_NOT_BE_LOADED_LMAO_DUMBASS");
		}

		glm::mat4 viewMatrix = glm::mat4(1.0f);
		viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));
		currentViewMatrix = viewMatrix;
	}

	void Entity::Render(glm::mat4 viewMatrix) {
		currentShader->use();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, GL_Texture1);

		// Model matrix to convert local space to world space
		glm::mat4 modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(transform.x, transform.y, transform.z));

		currentViewMatrix = viewMatrix;

		// Projection matrix to convert view space to clip space (perspective)
		glm::mat4 projectionMatrix = glm::mat4(1.0f);
		projectionMatrix = glm::perspective(glm::radians(45.0f), (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);

		// Send matrices to shader
		currentShader->setMatrix4fv("model", 1, GL_FALSE, glm::value_ptr(modelMatrix));
		currentShader->setMatrix4fv("view", 1, GL_FALSE, glm::value_ptr(viewMatrix));
		currentShader->setMatrix4fv("projection", 1, GL_FALSE, glm::value_ptr(projectionMatrix));

		glBindVertexArray(GL_VAO);
		glDrawArrays(GL_TRIANGLES, 0, (GLsizei)m_vertices.size());
		glBindVertexArray(0);
	}

	void Entity::Render() {
		currentShader->use();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, GL_Texture1);

		// Model matrix to convert local space to world space
		glm::mat4 modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(transform.x, transform.y, transform.z));

		// Projection matrix to convert view space to clip space (perspective)
		glm::mat4 projectionMatrix = glm::mat4(1.0f);
		projectionMatrix = glm::perspective(glm::radians(45.0f), (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);

		// Send matrices to shader
		currentShader->setMatrix4fv("model", 1, GL_FALSE, glm::value_ptr(modelMatrix));
		currentShader->setMatrix4fv("view", 1, GL_FALSE, glm::value_ptr(currentViewMatrix));
		currentShader->setMatrix4fv("projection", 1, GL_FALSE, glm::value_ptr(projectionMatrix));

		glBindVertexArray(GL_VAO);
		glDrawArrays(GL_TRIANGLES, 0, (GLsizei)m_vertices.size());
		glBindVertexArray(0);
	}
}