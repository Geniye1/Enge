#include "Texture.h"

namespace Enge {

	bool Texture::LoadTexture(const char* texturePath, GLuint* GL_Texture, Shader* shader) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

		// Set the texture filters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // Interpolated mipmaps
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  // Interpolated texits

		LOG(ENGE_INFO, "TEXTURE SETTINGS SET...\n");

		// Generate textures
		glGenTextures(1, GL_Texture);

		// Bind the first texture unit
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, *GL_Texture);

		// Flip the image since OpenGL expects 0.0 to be on the bottom of the screen
		stbi_set_flip_vertically_on_load(true);

		// Load the textures with the stb_image helper
		int width, height, nrChannels;
		unsigned char* data;
		data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
		if (!data) {
			LOG_ERR("FAILED TO LOAD TEXTURE DUMBASS\n");
			return false;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data); // Free the image memory

		// Set each texture uniform to the proper texture unit that it is associated with
		shader->use();
		shader->setInt("texture1", 0);
	}

}