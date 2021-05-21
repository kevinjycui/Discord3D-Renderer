#include "../include/main.h"
#include "../include/texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"


unsigned int texture;

void GenerateTexture()
{
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);  
	unsigned char *data = stbi_load("assets/texture.jpg", &width, &height, &nrChannels, 0);
	
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture\n";
	}

	stbi_image_free(data);
}
