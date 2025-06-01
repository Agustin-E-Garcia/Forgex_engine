#include "TextureLoader.h"
#include <GL/glew.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <ForgexDebugTools.h>

namespace Forgex::Graphics::Utils
{
    struct TextureInfo
    {
        int m_InternalFormat;
        int m_Width;
        int m_Height;
        unsigned int m_Format;
        unsigned int m_Type;
    };
    
    unsigned int GenerateTexture(TextureType type, TextureInfo info, const void* data)
    {
        unsigned int textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, info.m_InternalFormat, info.m_Width, info.m_Height, 0, info.m_Format, info.m_Type, data);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glBindTexture(GL_TEXTURE_2D, 0);
        return textureID;
    }
    
    int TextureLoader::LoadDefaultTexture(TextureType type, const char* file)
    {
        LOG_CORE(Debug::Info, "Loading Texture '{0}'", file);
        stbi_set_flip_vertically_on_load(true);
        
        int width, height, nrChannels;
        const unsigned char* image = stbi_load(file, &width, &height, &nrChannels, 0);

        if(!image)
        {
            LOG_CORE(Debug::Error, "Failed to load Texture '{0}'", file);
            return -1;
        }
        
        return GenerateTexture(type, {GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE}, image);
    }

    
    int TextureLoader::LoadCubemapTexture(TextureType type, std::vector<const char*> filePaths)
    {
        stbi_set_flip_vertically_on_load(false);
        unsigned int textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
        
        int width, height, nrChannels;
        for (unsigned int i = 0; i < filePaths.size(); i++)
        {
            unsigned char* data = stbi_load(filePaths[i], &width, &height, &nrChannels, 0);
            if (data)
            {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                stbi_image_free(data);
            }
            else
            {
                LOG_CORE(Debug::Error, "Failed to load cubemap texture '{0}'", filePaths[i]);
                stbi_image_free(data);
                glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
                return -1;
            }
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
        return textureID;
    }
}
