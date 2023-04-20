#include "Texture.h"

Texture::Texture(const std::string& path)
{
	glGenTextures(1, &id);

	LoadTexture(path);
}

void Texture::Use()
{
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::LoadTexture(const std::string path)
{
	glBindTexture(GL_TEXTURE_2D, id);

	int width, height, nChannels;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nChannels, 0);

	GLenum format = GL_RED;

	switch (nChannels)
	{
	case 4:
		format = GL_RGBA;
		break;
	case 3:
		format = GL_RGB;
		break;
	}

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture at path: " << path << std::endl;
	}

	stbi_image_free(data);
}
