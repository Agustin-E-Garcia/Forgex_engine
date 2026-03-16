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

        void CalculateMesh();
        void GenerateMesh();

        int vertexBufferID;

        glm::vec3 Interpolate(glm::vec3 posA, glm::vec3 posB, uint8_t valA, uint8_t valB);
        glm::vec3 GetSamplePosition(int sampleID);
        int GetSampleID(glm::vec3 position);
        void PushVertex(glm::vec3 vertex, glm::vec3 normal);

        float* GetVertices() { return m_Vertices.data(); }
        int GetVertexCount() { return m_Vertices.size() / 6; }
        glm::mat4 GetModelMatrix() { return m_ChunkModelMatrix; }

    private:
        glm::vec3 m_ChunkPosition = glm::vec3(0.0f);
        glm::vec3 m_ChunkSize = glm::vec3(64.0f);
        glm::ivec3 m_Samples;

        std::vector<uint8_t> m_DensityValues;

        std::vector<float> m_Vertices;
        glm::mat4 m_ChunkModelMatrix = glm::mat4(1.0f);
    };
}
