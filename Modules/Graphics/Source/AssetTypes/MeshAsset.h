#pragma once
#include <string>
#include <ForgexAssets.h>
#include <ForgexCore.h>

#include "../Utils/BufferManager.h"

namespace Forgex::Graphics
{
    class MeshAsset : public Assets::Asset
    {
    public:
        MeshAsset(std::string assetPath) : Assets::Asset(assetPath) {}
        MeshAsset(std::string assetPath, const float* vertexData, int vertexSize, const int* indexData = nullptr, int indexSize = -1)
            : m_IndexBufferSize(indexSize), Assets::Asset(assetPath, true)
        {
            GenerateBuffers(vertexData, vertexSize, indexData, indexSize);
        }

        bool Load() override
        {
            LOG_CORE(Debug::LogLevel::Info, "Loading MeshAsset: '{0}'", m_Path);

            Assets::Files::MeshData data;
            if(!Assets::Files::ReadFile(m_Path.c_str(), data))
            {
                LOG_CORE(Debug::Error, "Failed to load MeshAsset {0}", m_Path);
                return false;
            }

            GenerateBuffers(data.m_Vertices.data(), data.m_Vertices.size(), data.m_Indices.data(), data.m_Indices.size());
            m_IndexBufferSize = data.m_Indices.size();

            return true;
        }

        void GenerateBuffers(const float* vertexData, int vertexSize, const int* indexData, int indexSize)
        {
            if(vertexData) m_VertexBufferID = Utils::BufferManager::GenerateBuffer(Utils::BufferType::VertexBuffer, vertexSize * sizeof(float), vertexData);
            if(indexData)  m_IndexBufferID = Utils::BufferManager::GenerateBuffer(Utils::BufferType::IndexBuffer, indexSize * sizeof(int), indexData);

            m_GPUSize = vertexSize * sizeof(float) + indexSize * sizeof(int);
        }

        void Unload() override
        {
            Utils::BufferManager::DeleteBuffer(m_IndexBufferID);
            Utils::BufferManager::DeleteBuffer(m_VertexBufferID);
        }

        bool Save(const std::string& assetPath) override
        {
            LOG_CORE(Debug::LogLevel::Info, "Saving MeshAsset: '{0}'", assetPath);
            return true;
        }

        int GetVertexBuffer() { return m_VertexBufferID; }
        int GetIndexBuffer() { return m_IndexBufferID; }
        int GetIndexBufferCount() { return m_IndexBufferSize; }

        size_t GetCPUMemorySize() const override { return sizeof(*this); }

    private:
        int m_VertexBufferID = -1;
        int m_IndexBufferID = -1;
        int m_IndexBufferSize = -1;
    };
}
