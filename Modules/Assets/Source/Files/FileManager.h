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
        int m_Channels = -1;

        TextureData();
        ~TextureData();
        TextureData(const TextureData&) = delete;
        TextureData& operator=(const TextureData&) = delete;
    };

    struct MeshData
    {
        std::vector<float> m_Vertices; // vx, vy, vz, nx, ny, nz, uvx, uvy
        std::vector<int> m_Indices;

        MeshData();
        ~MeshData();
        MeshData(const MeshData&) = delete;
        MeshData& operator=(const MeshData&) = delete;
    };

    bool ReadFile(const char* filePath, std::string& buffer);
    bool ReadFile(const char* filePath, std::vector<std::string>& buffers);
    bool ReadFile(const char* filePath, TextureData& textureData, bool flip = false);
    bool ReadFile(const char* filePath, MeshData& meshData);
}
