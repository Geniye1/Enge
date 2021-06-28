#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include "../Logger/Logger.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
	// Program ID
	unsigned int ID;

	// Constructor read and builds shader
	Shader(const char* vertexPath, const char* fragPath);
	// Use & activate the shader
	void use();
	// Utility functions
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;

	void setFloat4(const std::string& name, float v1, float v2, float v3, float v4) const;
};

#endif 

