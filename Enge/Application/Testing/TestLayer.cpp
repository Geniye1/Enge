#include "TestLayer.h"

namespace Enge {

	TestLayer::TestLayer(PerspectiveCameraController* perspectiveCameraCont)
		: Layer("TestLayer"), m_perspectiveCameraCont(perspectiveCameraCont)
	{

	}

	void TestLayer::OnStart() {
		vertices = {
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
		// vao, vbo, ebo, vertices, 
		glGenVertexArrays(1, &GL_VAO);
		glBindVertexArray(GL_VAO);
		
		// VBO
		glGenBuffers(1, &GL_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, GL_VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices.front(), GL_STATIC_DRAW);

		/*// IBO
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

		currentShader->loadShaderProgram("Application/Shaders/Base Shaders/BaseVertexShader.glsl", "Application/Shaders/Base Shaders/BaseFragmentShader.glsl");

		// Texturing

		// Set the texture to mirror and repeat in both the S and T directions
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

		// Set the texture filters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // Interpolated mipmaps
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  // Interpolated texits

		LOG(ENGE_INFO, "TEXTURE SETTINGS SET...\n");

		// Generate textures
		glGenTextures(1, &GL_Texture1);
		glGenTextures(1, &GL_Texture2);

		// Bind the first texture unit
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, GL_Texture1);

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
		glBindTexture(GL_TEXTURE_2D, GL_Texture2);

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
		currentShader->use();
		currentShader->setInt("texture1", 0);
		currentShader->setInt("texture2", 1);

		LOG(ENGE_INFO, "TEXTURES SUCCESSFULLY LOADED...");
	}

	void TestLayer::OnEnd() {

	}

	void TestLayer::OnUpdate(float dt) {

		// Rendering
		glClearColor(0.22f, 0.22f, 0.22f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		currentShader->use();

		// fuckin with the uniform
		float timeValue = (float)glfwGetTime();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, GL_Texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, GL_Texture2);


		// MATRIX FUCKERY

		// Model matrix to convert local space to world space
		glm::mat4 modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::rotate(modelMatrix, timeValue * glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 1.0f));

		// View matrix to convert world space into view space (camera)
		m_perspectiveCameraCont->updateMouseLook();
		glm::mat4 viewMatrix = m_perspectiveCameraCont->updateCameraPosition(dt);
		
		// Projection matrix to convert view space to clip space (perspective)
		glm::mat4 projectionMatrix = glm::mat4(1.0f);
		projectionMatrix = glm::perspective(glm::radians(45.0f), (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);

		// Send matrices to shader
		currentShader->setMatrix4fv("model", 1, GL_FALSE, glm::value_ptr(modelMatrix));
		currentShader->setMatrix4fv("view", 1, GL_FALSE, glm::value_ptr(viewMatrix));
		currentShader->setMatrix4fv("projection", 1, GL_FALSE, glm::value_ptr(projectionMatrix));





		glBindVertexArray(GL_VAO);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		
	}

}