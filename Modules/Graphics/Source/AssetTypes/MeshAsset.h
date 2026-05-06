#pragma once
#include "../GraphicsExports.h"
#include <string>
#include <ForgexAssets.h>

namespace Forgex::Graphics
{
    struct MeshData
    {
        std::vector<float> m_Vertices; // vx, vy, vz, nx, ny, nz, uvx, uvy
        std::vector<int> m_Indices;
    };

    class GRAPHICS_API MeshAsset : public Assets::Asset
    {
    public:
        MeshAsset(std::string assetPath) : Assets::Asset(assetPath) {}
        MeshAsset(std::string assetPath, const float* vertexData, int vertexSize, const int* indexData = nullptr, int indexSize = -1)
            : m_IndexBufferSize(indexSize), Assets::Asset(assetPath, true)
        {
            GenerateBuffers(vertexData, vertexSize, indexData, indexSize);
        }

        bool Load() override;
        void Unload() override;
        bool Save(const std::string& assetPath) override { return false; }
        size_t GetCPUMemorySize() const override { return sizeof(*this); }

        int GetVertexBuffer() { return m_VertexBufferID; }
        int GetIndexBuffer() { return m_IndexBufferID; }
        int GetIndexBufferCount() { return m_IndexBufferSize; }
        void GenerateBuffers(const float* vertexData, int vertexSize, const int* indexData, int indexSize);

    private:
        int m_VertexBufferID = -1;
        int m_IndexBufferID = -1;
        int m_IndexBufferSize = -1;
    };
}
