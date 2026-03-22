#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Forgex::Assets::Files
{
    TextureData::TextureData() {}
    TextureData::~TextureData() { stbi_image_free(m_Image); }


    bool ReadFile(const char* filePath, std::string& buffer)
    {
        std::ifstream fileStream(filePath, std::ios::in);
        if (!fileStream.is_open()) return false;

        std::stringstream sstr;
        sstr << fileStream.rdbuf();
        buffer = sstr.str();
        fileStream.close();
        return true;
    }

    bool ReadFile(const char* filePath, std::vector<std::string>& buffers)
    {
        std::ifstream fileStream(filePath, std::ios::in);
        if (!fileStream.is_open()) return false;

        std::string line;
        while (std::getline(fileStream, line, ','))
        {
            while (!line.empty() && (line.back() == '\n' || line.back() == '\r' || line.back() == ' '))
                line.pop_back();

            if (!line.empty())
                buffers.push_back(line);
        }

        return !buffers.empty();
    }

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
