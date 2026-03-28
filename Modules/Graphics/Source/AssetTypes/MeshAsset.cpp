#include "MeshAsset.h"
#include "../Utils/BufferManager.h"

#include <ForgexFiles.h>

namespace Forgex::Graphics
{
    bool MeshAsset::Load()
    {
        LOG_CORE(Debug::Trace, "Loading MeshAsset: '{0}'", m_Path);

        nlohmann::json data;
        if(!Files::ReadMeshFile(m_Path.c_str(), data))
        {
            LOG_CORE(Debug::Error, "Failed to load MeshAsset {0}", m_Path);
            return false;
        }

        std::vector<float> vertices = data["vertices"];
        std::vector<int> indices = data["indices"];
        GenerateBuffers(vertices.data(), data["vertexCount"], indices.data(), data["indexCount"]);
        m_IndexBufferSize = data["indexCount"];

        return true;
    }

    void MeshAsset::GenerateBuffers(const float* vertexData, int vertexSize, const int* indexData, int indexSize)
    {
        if(vertexData) m_VertexBufferID = Utils::BufferManager::GenerateBuffer(Utils::BufferType::VertexBuffer, vertexSize * sizeof(float), vertexData);
        if(indexData)  m_IndexBufferID = Utils::BufferManager::GenerateBuffer(Utils::BufferType::IndexBuffer, indexSize * sizeof(int), indexData);

        m_GPUSize = vertexSize * sizeof(float) + indexSize * sizeof(int);
    }

    void MeshAsset::Unload()
    {
        Utils::BufferManager::DeleteBuffer(m_IndexBufferID);
        Utils::BufferManager::DeleteBuffer(m_VertexBufferID);
    }
}
