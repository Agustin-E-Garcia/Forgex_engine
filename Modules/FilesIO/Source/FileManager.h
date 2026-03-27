#pragma once
#include <string>
#include <vector>
#include <json.hpp>

namespace Forgex::Files
{
    struct TextureData
    {
        unsigned char* m_Image = nullptr;
        int m_Width = -1;
        int m_Height = -1;
        int m_Channels = -1;

        TextureData();
        ~TextureData();
        TextureData(const TextureData&) = delete;
        TextureData& operator=(const TextureData&) = delete;
    };

    bool WriteFile(const char* filePath, nlohmann::json& data);

    bool ReadFile(const char* filePath, nlohmann::json& data, std::string& err);
    bool ReadMeshFile(const char* filePath, nlohmann::json& data);

    bool ReadFile(const char* filePath, std::string& buffer);
    bool ReadFile(const char* filePath, std::vector<std::string>& buffers);
    bool ReadFile(const char* filePath, TextureData& textureData, bool flip = false);
}
