#pragma once
#include "../Components/VoxelChunk.h"
#include "TerrainGenerator.h"

namespace Forgex::Voxel::Utils
{
    class ChunkMesher
    {
    public:
        ChunkMesher(const Components::Chunk* chunk, TerrainGenerator* generator);
        ~ChunkMesher();

        void GenerateMesh(std::vector<float>& vertices, std::vector<int>& indices);

    private:
        const Components::Chunk* m_Chunk = nullptr;
        TerrainGenerator* m_Generator = nullptr;
        std::unordered_map<uint64_t, uint32_t> m_VertexToIndexMap;

        uint32_t GetOrAddVertexIndex(std::vector<float>& vertices, glm::vec3 posA, glm::vec3 posB);
        glm::vec3 CalculateSampleGradientNormal(glm::vec3 vertexLocalPos);
        glm::vec3 Interpolate(glm::vec3 posA, glm::vec3 posB, uint8_t valA, uint8_t valB);
        uint64_t GetSampleID(glm::vec3 position);
        uint32_t PushVertex(std::vector<float>& vertices, glm::vec3 vertex, glm::vec3 normal);
    };
}
