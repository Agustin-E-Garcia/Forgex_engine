#pragma once
#include <glm/glm.hpp>
#include <vector>

namespace Forgex::Voxel
{
    class Chunk
    {
    public:
        Chunk(glm::vec3 chunkPos, glm::vec3 size);
        ~Chunk();

        static float s_Cutoff;
        static float s_SampleDensity;
        static int s_NoiseSeed;
        static float s_TopMapY;

        int vertexBufferID; // Leaving this here for now, once we move this to be components it'll be saved somwhere else
        int indexBufferID;

        float* GetVertices() { return m_Vertices.data(); }
        int GetVertexCount() { return m_Vertices.size() / 6; }

        uint32_t* GetIndices() { return m_Indices.data(); }
        int GetIndexCount() { return m_Indices.size(); }

        glm::mat4 GetModelMatrix() { return m_ChunkModelMatrix; }

    private:
        glm::vec3 m_ChunkPosition = glm::vec3(0.0f);
        glm::vec3 m_ChunkSize = glm::vec3(64.0f);
        glm::ivec3 m_Samples = glm::vec3(-10.f);

        std::vector<uint8_t> m_DensityValues;

        std::unordered_map<uint64_t, uint32_t> m_VertexToIndexMap;
        std::vector<float> m_Vertices;
        std::vector<uint32_t> m_Indices;
        glm::mat4 m_ChunkModelMatrix = glm::mat4(1.0f);

        bool GenerateDensity();
        void GenerateMesh();

        uint32_t GetOrAddVertexIndex(glm::vec3 posA, glm::vec3 posB);
        glm::vec3 CalculateSampleGradientNormal(glm::vec3 vertexLocalPos);
        uint8_t GetDensityValueAtPoint(glm::vec3 position, float* surfaceHeight);
        glm::vec3 Interpolate(glm::vec3 posA, glm::vec3 posB, uint8_t valA, uint8_t valB);
        glm::vec3 GetSamplePosition(int sampleID);
        uint64_t GetSampleID(glm::vec3 position);
        uint32_t PushVertex(glm::vec3 vertex, glm::vec3 normal);
    };
}
