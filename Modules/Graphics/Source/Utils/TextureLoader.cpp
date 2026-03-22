#include "TextureLoader.h"
#include <GL/glew.h>

#include <ForgexCore.h>
#include <ForgexAssets.h>

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

    unsigned int GenerateTexture(Assets::Files::TextureData& data, int internalFormat, unsigned int format, int dataType)
    {
        unsigned int textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, data.m_Width, data.m_Height, 0, format, dataType, data.m_Image);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glBindTexture(GL_TEXTURE_2D, 0);
        return textureID;
    }

    int TextureLoader::LoadTexture(const char* file)
    {
        LOG_CORE(Debug::Info, "Loading Texture '{0}'", file);

        Assets::Files::TextureData textureData;
        if(!Assets::Files::ReadFile(file, textureData, true))
        {
            LOG_CORE(Debug::Error, "Failed to load Texture '{0}'", file);
            return -1;
        }

        unsigned int textureID = GenerateTexture(textureData, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);
        return textureID;
    }


    int TextureLoader::LoadTexture(std::vector<std::string> filePaths)
    {
        unsigned int textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

        for(unsigned int i = 0; i < filePaths.size(); i++)
        {
            Assets::Files::TextureData textureData;
            if(!Assets::Files::ReadFile(filePaths[i].c_str(), textureData))
            {
                LOG_CORE(Debug::Error, "Failed to load cubemap texture '{0}'", filePaths[i]);
                glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
                return -1;
            }

            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, textureData.m_Width, textureData.m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData.m_Image);
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
        return textureID;
    }

    void TextureLoader::UnloadTexture(unsigned int textureID)
    {
        glDeleteTextures(1, &textureID);
    }
}
