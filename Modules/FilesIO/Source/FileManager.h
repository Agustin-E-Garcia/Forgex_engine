#pragma once
#include "FileExports.h"
#include <string>
#include <vector>
#include <json.hpp>

namespace Forgex::Files
{
    struct FILES_API TextureData
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

    bool FILES_API WriteFile(const char* filePath, nlohmann::json& data);

    bool FILES_API ReadFile(const char* filePath, nlohmann::json& data, std::string& err);
    bool FILES_API ReadMeshFile(const char* filePath, nlohmann::json& data);

    bool FILES_API ReadFile(const char* filePath, std::string& buffer);
    bool FILES_API ReadFile(const char* filePath, std::vector<std::string>& buffers);
    bool FILES_API ReadFile(const char* filePath, TextureData& textureData, bool flip = false);
}
