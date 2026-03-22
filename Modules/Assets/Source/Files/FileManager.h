#pragma once
#include <string>
#include <vector>

namespace Forgex::Assets::Files
{
    struct TextureData
    {
        unsigned char* m_Image = nullptr;
        int m_Width = -1;
        int m_Height = -1;

        TextureData();
        ~TextureData();
        TextureData(const TextureData&) = delete;
        TextureData& operator=(const TextureData&) = delete;
    };

    bool ReadFile(const char* filePath, std::string& buffer);
    bool ReadFile(const char* filePath, std::vector<std::string>& buffers);
    bool ReadFile(const char* filePath, TextureData& textureInfo, bool flip = false);
}
