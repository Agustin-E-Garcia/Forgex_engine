#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Forgex::Assets::Files
{
    bool ReadFile(const char* filePath, std::string& buffer)
    {
        std::ifstream fileStream(filePath, std::ios::in);
        if (fileStream.is_open())
        {
            std::stringstream sstr;
            sstr << fileStream.rdbuf();
            buffer = sstr.str();
            fileStream.close();
            return true;
        }

        return false;
    }

    TextureData::TextureData() {}
    TextureData::~TextureData() { stbi_image_free(m_Image); }

    bool ReadFile(const char* filePath, TextureData& textureData, bool flip)
    {
        stbi_set_flip_vertically_on_load(flip);

        int width, height, nrChannels;
        unsigned char* image = stbi_load(filePath, &width, &height, &nrChannels, 0);

        if(!image) return false;

        textureData.m_Image = image;
        textureData.m_Width = width;
        textureData.m_Height = height;

        return true;
    }
}
