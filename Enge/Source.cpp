#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shaders/ShaderFilesUtil.h"
#include "Logger/Logger.h"

#include <iostream>
#include <assert.h>

void glfw_error_callback(int error, const char* description);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

/*float vertices[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
};
unsigned int indices[] = {  // note that we start from 0!
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
};*/

float vertices[] = {
	-1.0f, -0.5f, 0.0f,
	-0.5f,  0.5f, 0.0f,
	 0.0f, -0.5f, 0.0f,
	 0.5f, 0.5f, 0.0f,
	 1.0f, -0.5f, 0.0f
};

unsigned int indices[] = {
	0, 1, 2, // First tri
	2, 3, 4  // Second tri
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

	LOG('i', "GLFW WINDOW SUCCESSFULLY CREATED...\n");

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// =======================================================================

	// SHADERS
	// ===============================================================

	// Read in the GLSL files
	const char* vertexShaderSource;
	const char* fragmentShaderSource;

	vertexShaderSource = readInShaderFile("Shaders/Base Shaders/BaseVertexShader.glsl");
	fragmentShaderSource = readInShaderFile("Shaders/Base Shaders/BaseFragmentShader.glsl");

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Check if the shader was compiled successfully
	int vSuccess, fSuccess;
	char vInfoLog[512], fInfoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vSuccess);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fSuccess);

	if (!vSuccess) {
		glGetShaderInfoLog(vertexShader, 512, NULL, vInfoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << vInfoLog << std::endl;
	}
	if (!fSuccess) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, fInfoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << fInfoLog << std::endl;
	}

	// Create and link the shader program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Ensure the creation and link was successful
	int programSuccess;
	char pInfoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &programSuccess);
	if (!programSuccess) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, pInfoLog);
		std::cout << "ERROR::SHADER::PROGRAM::CREATION_LINK_FAILURE\n" << pInfoLog << std::endl;
	}

	// Use the program and clean up
	glUseProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	free((void*)vertexShaderSource);
	free((void*)fragmentShaderSource);

	// ================================================================

	// UNCOMMENT FOR WIREFRAME MODE
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	LOG('i', "ENTERING RENDER LOOP...\n");

	while (!glfwWindowShouldClose(window)) {
		// Input
		processInput(window);

		// Rendering
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 6);
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