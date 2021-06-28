#include "ShaderFilesUtil.h"

char* readInShaderFile(const char* filePath) {

	FILE* shaderFile;
	long fileSize;
	char* shaderSource = NULL;
	size_t readingResult;

	// Open the file for reading
	fopen_s(&shaderFile, filePath, "r");
	if (shaderFile == NULL) {
		std::cout << "ERROR::SHADER_FILES_UTIL::FILE_CANNOT_BE_OPENED" << stderr << std::endl;
		exit(1);
	}

	// Get the file size
	fseek(shaderFile, -6, SEEK_END);
	fileSize = ftell(shaderFile);
	rewind(shaderFile);

	// Allocate the needed memory
	shaderSource = (char*)malloc(sizeof(char) * fileSize+1);
	if (shaderSource == NULL) {
		std::cout << "ERROR::SHADER_FILES_UTIL::MEMORY_ERROR" << stderr << std::endl;
		fclose(shaderFile);
		free(shaderSource);
		exit(2);
	}

	// Copy the file into the buffer
	readingResult = fread(shaderSource, sizeof(char), fileSize, shaderFile);
	if (readingResult != fileSize) {
		std::cout << "ERROR::SHADER_FILES_UTIL::READING__ERROR" << stderr << std::endl;
		std::cout << "Calculated File Size: " << fileSize << ", Read in size: " << readingResult << std::endl;
		std::cout << "RESULT: " << shaderSource << std::endl;
		fclose(shaderFile);
		free(shaderSource);
		exit(3);
	}

	// Add the EOF character
	shaderSource[fileSize] = '\0';
	
	fclose(shaderFile);

	return shaderSource;

}