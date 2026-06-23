#pragma once
#include "../Components/Chunk.h"
#include <cstdint>
#include <vector>

namespace Forgex::Voxel::Utils
{
    class ChunkMesher
    {
    public:
        // Operates on a caller-owned copy of the density values so the live chunk
        // can be moved or destroyed while the mesh is being generated on a worker thread.
        ChunkMesher(const Components::ChunkData& chunk);
        ~ChunkMesher();

        void GenerateMesh(std::vector<float>& vertices, std::vector<int>& indices);

    private:
        const Components::ChunkData& m_Chunk;
        glm::vec3 m_Samples = glm::vec3(0);
        std::unordered_map<uint64_t, uint32_t> m_VertexToIndexMap;

        uint32_t GetOrAddVertexIndex(std::vector<float>& vertices, glm::vec3 posA, glm::vec3 posB);
        glm::vec3 CalculateSampleGradientNormal(glm::vec3 vertexLocalPos);
        float SampleDensity(glm::vec3 localPos);
        glm::vec3 Interpolate(glm::vec3 posA, glm::vec3 posB, int8_t valA, int8_t valB);
        uint64_t GetSampleID(glm::vec3 position);
        uint32_t PushVertex(std::vector<float>& vertices, glm::vec3 vertex, glm::vec3 normal);
    };
}
