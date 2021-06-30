#include "Renderer.h"

namespace Enge {

	void Renderer::RendererInit(GLFWwindow& currentWindow) {
		float vertices[] = {
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};

		unsigned int vao, vbo, ebo;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// VBO
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		/*// EBO
		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

		// Attributes
		// Position attribs
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);

		// Color attribs
		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		//glEnableVertexAttribArray(1);

		// Texture coord attribs
		//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		//glEnableVertexAttribArray(2);

		// =======================================================================

		// UNCOMMENT FOR WIREFRAME MODE
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		LOG(ENGE_DEBUG, "ENTERING RENDER LOOP...\n");

		Shader currentShader("Application/Shaders/Base Shaders/BaseVertexShader.glsl", "Application/Shaders/Base Shaders/BaseFragmentShader.glsl");

		// Texturing

		// Set the texture to mirror and repeat in both the S and T directions
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

		// Set the texture filters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // Interpolated mipmaps
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  // Interpolated texits

		LOG(ENGE_INFO, "TEXTURE SETTINGS SET...\n");

		// Generate textures
		unsigned int texture1, texture2;
		glGenTextures(1, &texture1);
		glGenTextures(1, &texture2);

		// Bind the first texture unit
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);

		// Flip the image since OpenGL expects 0.0 to be on the bottom of the screen
		stbi_set_flip_vertically_on_load(true);

		// Load the textures with the stb_image helper
		int width, height, nrChannels;
		unsigned char* data;
		data = stbi_load("Application/Rsc/rocks.jpg", &width, &height, &nrChannels, 0);
		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			LOG_ERR("FAILED TO LOAD TEXTURE DUMBASS\n");
		}
		stbi_image_free(data); // Free the image memory

		// Bind the second texture unit
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		data = stbi_load("Application/Rsc/awesomeface.png", &width, &height, &nrChannels, 0);
		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			LOG_ERR("FAILED TO LOAD TEXTURE DUMBASS\n");
		}
		stbi_image_free(data); // Free the image memory

		// Set each texture uniform to the proper texture unit that it is associated with
		currentShader.use();
		currentShader.setInt("texture1", 0);
		currentShader.setInt("texture2", 1);

		LOG(ENGE_INFO, "TEXTURES SUCCESSFULLY LOADED...");



		while (!glfwWindowShouldClose(&currentWindow)) {
			// Input
			//processInput(window);

			// Rendering
			glClearColor(0.22f, 0.22f, 0.22f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			currentShader.use();

			// fuckin with the uniform
			float timeValue = (float)glfwGetTime();

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture1);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, texture2);


			// MATRIX FUCKERY

			// Model matrix to convert local space to world space
			glm::mat4 modelMatrix = glm::mat4(1.0f);
			modelMatrix = glm::rotate(modelMatrix, timeValue / 2 * glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 1.0f));

			// View matrix to convert world space into view space (camera)
			glm::mat4 viewMatrix = glm::mat4(1.0f);
			viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));

			// Projection matrix to convert view space to clip space (perspective)
			float fovChange = (sin(timeValue) / 2.0f + 0.5f) * 20;
			glm::mat4 projectionMatrix = glm::mat4(1.0f);
			projectionMatrix = glm::perspective(glm::radians(45.0f + fovChange), (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);

			// Send matrices to shader
			currentShader.setMatrix4fv("model", 1, GL_FALSE, glm::value_ptr(modelMatrix));
			currentShader.setMatrix4fv("view", 1, GL_FALSE, glm::value_ptr(viewMatrix));
			currentShader.setMatrix4fv("projection", 1, GL_FALSE, glm::value_ptr(projectionMatrix));





			glBindVertexArray(vao);
			//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glBindVertexArray(0);

			glfwSwapBuffers(&currentWindow);
			glfwPollEvents();
		}
	}

}