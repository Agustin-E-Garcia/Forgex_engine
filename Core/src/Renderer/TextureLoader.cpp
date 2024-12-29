#include "pch.h"
#include "TextureLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <GL/glew.h>
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

unsigned int TextureLoader::LoadCubemapTexture(std::vector<const char*> filePaths)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < filePaths.size(); i++)
    {
        LOG_CORE_INFO("Loading texture '{0}'", filePaths[i]);

        unsigned char* data = stbi_load(filePaths[i], &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            LOG_CORE_ERROR("Failed to load cubemap texture at path {0}", filePaths[i]);
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
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