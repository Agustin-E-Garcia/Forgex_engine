#include "TextureLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "GL/glew.h"
#include "Log.h"

unsigned int TextureLoader::LoadTexture(const char* filePath)
{
	LOG_CORE_INFO("Loading texture '{0}'", filePath);

	int width, height;
	unsigned char* image = stbi_load(filePath, &width, &height, nullptr, STBI_rgb_alpha);

	if (image == nullptr) LOG_CORE_ERROR("Failed to load texture '{0}'", filePath);

	return GenerateTexture(GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);
}

unsigned int TextureLoader::LoadHeightmapIntoTexture(float* pixels, int width, int height) 
{
	std::vector<unsigned char> image(width * height * 3);
	for (int i = 0; i < width * height; i++)
	{
		unsigned char value = static_cast<unsigned char>(pixels[i] * 255.0f);
		image[i * 3 + 0] = value;
		image[i * 3 + 1] = value;
		image[i * 3 + 2] = value;
	};

	return GenerateTexture(GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, image.data());
}

unsigned int TextureLoader::GenerateTexture(unsigned int internalFormat, int width, int height, unsigned int format, unsigned int type, const void* data)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	return textureID;
}