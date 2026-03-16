#include "VoxelChunk.h"
#include "Resources/MarchingCubesTable.h"
#include <ForgexDebugTools.h>
#include <glm/ext/matrix_transform.hpp>
#include <FastNoiseLite.h>

namespace Forgex::Voxel
{
    float Chunk::s_Cutoff = 127;
    float Chunk::s_SampleDensity = 0.5f;
    int Chunk::s_NoiseSeed = 1337;
    float Chunk::s_TopMapY = -1.0f;

    Chunk::Chunk(glm::vec3 chunkPos, glm::vec3 size) : m_ChunkSize(size), m_ChunkPosition(chunkPos)
    {
        m_ChunkModelMatrix = glm::translate(glm::mat4(1.0f), (chunkPos * size));

        bool shouldGenerateMesh = GenerateDensity();
        if(shouldGenerateMesh) GenerateMesh();
    }

    Chunk::~Chunk() {}

    bool Chunk::GenerateDensity()
    {
        m_Samples = (m_ChunkSize / glm::vec3(s_SampleDensity)) + glm::vec3(1.0f);
        int totalSamples = (int)m_Samples.x * (int)m_Samples.y * (int)m_Samples.z;
        m_DensityValues.resize(totalSamples, 255);

        FastNoiseLite noise;
        noise.SetSeed(s_NoiseSeed);
        noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
        noise.SetFractalType(FastNoiseLite::FractalType_FBm);

        glm::vec3 worldOffset = m_ChunkPosition * m_ChunkSize;

        bool hasAir = false;
        bool hasGround = false;
        for(int i = 0; i < m_DensityValues.size(); i++)
        {
            glm::vec3 worldPosition = worldOffset + GetSamplePosition(i);
            float n = noise.GetNoise(worldPosition.x, worldPosition.z);
            float surfaceHeight = (n + 1.0f) / 2.0f * m_ChunkSize.y;
            float density = (surfaceHeight - worldPosition.y) / m_ChunkSize.y * 255.0f;
            m_DensityValues[i] = (uint8_t)glm::clamp(density + 127.0f, 0.0f, 255.0f);

            if(worldPosition.y < surfaceHeight) hasGround = true;
            else hasAir = true;
        }

        return hasAir && hasGround;
    }

    void Chunk::GenerateMesh()
    {
        m_Vertices.reserve(m_Samples.x * m_Samples.y * m_Samples.z * 5 * 3 * 6);
        for (int z = 0; z < (int)m_Samples.z - 1; z++)
        for (int y = 0; y < (int)m_Samples.y - 1; y++)
        for (int x = 0; x < (int)m_Samples.x - 1; x++)
        {
            // We need the vectors to adhere to this order:
            //    4----5
            //   /|   /|
            //  7----6 |
            //  | 0--|-1
            //  |/   |/
            //  3----2

            glm::vec3 m_CornerPositions[8] =
            {
                glm::vec3(x    , y    , z + 1), // 0
                glm::vec3(x + 1, y    , z + 1), // 1
                glm::vec3(x + 1, y    , z    ), // 2
                glm::vec3(x    , y    , z    ), // 3
                glm::vec3(x    , y + 1, z + 1), // 4
                glm::vec3(x + 1, y + 1, z + 1), // 5
                glm::vec3(x + 1, y + 1, z    ), // 6
                glm::vec3(x    , y + 1, z    ), // 7
            };

            int m_CornerDensityValues[8] = 
            {
                m_DensityValues[GetSampleID(m_CornerPositions[0])], // 0
                m_DensityValues[GetSampleID(m_CornerPositions[1])], // 1
                m_DensityValues[GetSampleID(m_CornerPositions[2])], // 2
                m_DensityValues[GetSampleID(m_CornerPositions[3])], // 3
                m_DensityValues[GetSampleID(m_CornerPositions[4])], // 4
                m_DensityValues[GetSampleID(m_CornerPositions[5])], // 5
                m_DensityValues[GetSampleID(m_CornerPositions[6])], // 6
                m_DensityValues[GetSampleID(m_CornerPositions[7])], // 7
            };

            int caseID = 0;
            for (int i = 0; i < 8; i++)
            {
                if(m_CornerDensityValues[i] < s_Cutoff) continue;
                caseID |= (1 << i);
            }

            if(caseID == 0 || caseID == 255) continue; // if no sample is over cutoff, then we skip this cube

            for (int i = 0; i < 16; i += 3)
            {
                if(Resources::triTable[caseID][i] == -1) break;

                int index = Resources::triTable[caseID][i];
                int index_v1 = GetOrAddVertexIndex
                    (
                        m_CornerPositions[Resources::sidesTable[index][0]],
                        m_CornerPositions[Resources::sidesTable[index][1]]
                    );

                index = Resources::triTable[caseID][i + 1];
                int index_v2 = GetOrAddVertexIndex
                    (
                        m_CornerPositions[Resources::sidesTable[index][0]],
                        m_CornerPositions[Resources::sidesTable[index][1]]
                    );

                index = Resources::triTable[caseID][i + 2];
                int index_v3 = GetOrAddVertexIndex
                    (
                        m_CornerPositions[Resources::sidesTable[index][0]],
                        m_CornerPositions[Resources::sidesTable[index][1]]
                    );

                m_Indices.push_back(index_v1);
                m_Indices.push_back(index_v2);
                m_Indices.push_back(index_v3);

                CalculateNormal(index_v1, index_v2, index_v3);
           }
        }

        NormalizeNormals();
    }

    void Chunk::NormalizeNormals()
    {
        // We iterate starting at position 3 with a stride of 6 as to only modify the normals of each vertex
        for(int i = 3; i < m_Vertices.size(); i += 6)
        {
            glm::vec3 finalNormal = glm::normalize(glm::vec3(m_Vertices[i], m_Vertices[i + 1], m_Vertices[i + 2]));
            m_Vertices[i] = finalNormal.x;
            m_Vertices[i + 1] = finalNormal.y;
            m_Vertices[i + 2] = finalNormal.z;
        }
    }

    uint32_t Chunk::GetOrAddVertexIndex(glm::vec3 posA, glm::vec3 posB)
    {
        uint64_t idA = GetSampleID(posA);
        uint64_t idB = GetSampleID(posB);

        // We make sure we always have posA being the smaller number so it doesn't matter if we pass positions 0 - 1 or 1 - 0
        // We always get the same vertex that was generated between them
        if(idA > idB)
        {
            std::swap(idA, idB);
            std::swap(posA, posB);
        }

        uint64_t mapKey = idB << 32 | idA;

        if(m_VertexToIndexMap.contains(mapKey))
            return m_VertexToIndexMap[mapKey];

        glm::vec3 vertex = Interpolate(posA, posB, m_DensityValues[idA], m_DensityValues[idB]);
        uint32_t vertexIndex = PushVertex(vertex * s_SampleDensity);
        m_VertexToIndexMap[mapKey] = vertexIndex;

        return vertexIndex;
    }

    void Chunk::CalculateNormal(uint32_t index_v1, uint32_t index_v2, uint32_t index_v3)
    {
        glm::vec3 v1 = glm::vec3(m_Vertices[index_v1 * 6], m_Vertices[(index_v1 * 6) + 1], m_Vertices[(index_v1 * 6) + 2]);
        glm::vec3 v2 = glm::vec3(m_Vertices[index_v2 * 6], m_Vertices[(index_v2 * 6) + 1], m_Vertices[(index_v2 * 6) + 2]);
        glm::vec3 v3 = glm::vec3(m_Vertices[index_v3 * 6], m_Vertices[(index_v3 * 6) + 1], m_Vertices[(index_v3 * 6) + 2]);

        glm::vec3 normal = glm::cross(v3 - v1, v2 - v1);

        m_Vertices[(index_v1 * 6) + 3] += normal.x;
        m_Vertices[(index_v1 * 6) + 4] += normal.y;
        m_Vertices[(index_v1 * 6) + 5] += normal.z;

        m_Vertices[(index_v2 * 6) + 3] += normal.x;
        m_Vertices[(index_v2 * 6) + 4] += normal.y;
        m_Vertices[(index_v2 * 6) + 5] += normal.z;

        m_Vertices[(index_v3 * 6) + 3] += normal.x;
        m_Vertices[(index_v3 * 6) + 4] += normal.y;
        m_Vertices[(index_v3 * 6) + 5] += normal.z;
    }

    glm::vec3 Chunk::Interpolate(glm::vec3 posA, glm::vec3 posB, uint8_t valA, uint8_t valB)
    {
        float t = (s_Cutoff - valA) / (float)(valB - valA);
        return posA + t * (posB - posA);
    }

    glm::vec3 Chunk::GetSamplePosition(int sampleID)
    {
        glm::ivec3 samples = glm::ivec3((m_ChunkSize / glm::vec3(s_SampleDensity)) + glm::vec3(1.0f));

        int x = sampleID % samples.x;
        int y = (sampleID / samples.x) % samples.y;
        int z = sampleID / (samples.x * samples.y);

        return glm::vec3(x, y, z) * s_SampleDensity;
    }

    uint64_t Chunk::GetSampleID(glm::vec3 position)
    {
        return position.x + (position.y * m_Samples.x) + (position.z * m_Samples.x * m_Samples.y);
    }

    uint32_t Chunk::PushVertex(glm::vec3 vertex)
    {
        uint32_t index = GetVertexCount();
        // Add Vertex
        m_Vertices.push_back(vertex.x);
        m_Vertices.push_back(vertex.y);
        m_Vertices.push_back(vertex.z);
        // Add Normal
        m_Vertices.push_back(0.0f);
        m_Vertices.push_back(1.0f);
        m_Vertices.push_back(0.0f);

        return index;
    }
}
