#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Logger/Logger.h"
#include "Shaders/Shader.h"

#include "ThirdPartHelpers/stb_image.h"

#include <iostream>
#include <assert.h>

void glfw_error_callback(int error, const char* description);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

float vertices[] = {
	 // Positions        // Colors          // Texture Coords
	 0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,       // Top right
	 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,		  // Bottom right
	-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,		  // Bottom left
	-0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f		  // Top left
};
unsigned int indices[] = {  // note that we start from 0!
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
};

int main() {
	
	// Assertion to ensure the log can be opened, if fails the program will terminate
	assert(LOG_START());

	glfwSetErrorCallback(glfw_error_callback);

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	LOG('i', "STARTING CORE GLFW V%s\n\n", glfwGetVersionString());

	// IF ON MAC OS X
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "I can't type anymore", NULL, NULL);
	if (window == NULL) {
		LOG_ERR("ERROR::GLFW_WINDOW ### Failed to create GLFW window lmao imagine sucking\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	LOG('w', "GLFW WINDOW SUCCESSFULLY CREATED...\n");

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		LOG_ERR("ERROR:::GLAD ### Failed to initialize GLAD god damn\n");
		return -1;
	}

	LOG('i', "GLAD SUCCESSFULLY LOADED...\n");

	glViewport(0, 0, 800, 600); // (0,0) is the lower left corner, (800,600) is the top right corner
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // Callback function so when the window is resized the render viewport is also resized

	// VBO FUCKERY
	// =======================================================================
	// VAO
	unsigned int vao, vbo, ebo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// VBO
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// EBO
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Attributes
	// Position attribs
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Color attribs
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Texture coord attribs
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// =======================================================================

	// UNCOMMENT FOR WIREFRAME MODE
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	LOG('d', "ENTERING RENDER LOOP...\n");

	Shader currentShader("Shaders/Base Shaders/BaseVertexShader.glsl", "Shaders/Base Shaders/BaseFragmentShader.glsl");

	// Texturing

	// Set the texture to mirror and repeat in both the S and T directions
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	// Set the texture filters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // Interpolated mipmaps
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  // Interpolated texits

	LOG('i', "TEXTURE SETTINGS SET...\n");

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
	data = stbi_load("Rsc/container.jpg", &width, &height, &nrChannels, 0);
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

	data = stbi_load("Rsc/awesomeface.png", &width, &height, &nrChannels, 0);
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

	LOG('i', "TEXTURES SUCCESSFULLY LOADED...");

	// MATRIX FUCKERY

	

	while (!glfwWindowShouldClose(window)) {
		// Input
		processInput(window);

		// Rendering
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		currentShader.use();

		// fuckin with the uniform
		float timeValue = (float)glfwGetTime();

		// Identity matrix
		glm::mat4 trans = glm::mat4(1.0f);
		// Create a translational matrix that moves the vector to the bottom right of the screen
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		// Create a rotational matrix that rotates a vector 90 degrees clockwise around the z axis
		trans = glm::rotate(trans, timeValue, glm::vec3(0.0, 0.0, 1.0));

		unsigned int transformLoc = glGetUniformLocation(currentShader.ID, "transform");
		// Send the matrix to the vertex shader (glm::value_ptr() is required since glm stores the matrix in
		// a way that will make OpenGL shit itself so this function converts it)
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void glfw_error_callback(int error, const char* description) {
	LOG_ERR("GLFW ERROR: code %i, msg: %s\n", error, description);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}