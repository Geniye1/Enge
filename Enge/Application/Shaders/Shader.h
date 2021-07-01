#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Logger/Logger.h"

#include "../Enge_PCH.h"

class Shader {
public:
	// Program ID
	unsigned int ID;

	Shader() = default;
	
	void loadShaderProgram(const char* vertexPath, const char* fragPath);
	void use() const;

	// Utility functions
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setFloat4(const std::string& name, float v1, float v2, float v3, float v4) const;
	void setMatrix4fv(const std::string& name, int nOfMatrices, bool transpose, const GLfloat* value) const;
};

#endif 

