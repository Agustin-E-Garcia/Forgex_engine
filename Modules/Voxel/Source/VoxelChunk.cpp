#include "VoxelChunk.h"
#include "Resources/MarchingCubesTable.h"
#include <glm/ext/matrix_transform.hpp>
#include <FastNoiseLite.h>

namespace Forgex::Voxel
{
    float Chunk::s_Cutoff = 127;
    float Chunk::s_SampleDensity = 0.5f;

    Chunk::Chunk(glm::vec3 chunkPos, glm::vec3 size) : m_ChunkSize(size), m_ChunkPosition(chunkPos)
    {
        m_ChunkModelMatrix = glm::translate(glm::mat4(1.0f), chunkPos);

        CalculateMesh();
        GenerateMesh();
    }
    Chunk::~Chunk() {}

    void Chunk::CalculateMesh()
    {
        m_Samples = (m_ChunkSize / glm::vec3(s_SampleDensity)) + glm::vec3(1.0f);
        int totalSamples = (int)m_Samples.x * (int)m_Samples.y * (int)m_Samples.z;
        m_DensityValues.resize(totalSamples, 255);

        FastNoiseLite noise;
        noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
        noise.SetFractalType(FastNoiseLite::FractalType_FBm);

        for(int i = 0; i < m_DensityValues.size(); i++)
        {
            glm::vec3 position = GetSamplePosition(i);
            float n = noise.GetNoise(position.x, position.z); // 2D, only sample x and z
            float surfaceHeight = (n + 1.0f) / 2.0f * m_ChunkSize.y;
            m_DensityValues[i] = position.y < surfaceHeight ? 255 : 0;
        }
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
                glm::vec3 v1 = Interpolate
                (
                    m_CornerPositions[Resources::sidesTable[index][0]],
                    m_CornerPositions[Resources::sidesTable[index][1]],
                    m_CornerDensityValues[Resources::sidesTable[index][0]],
                    m_CornerDensityValues[Resources::sidesTable[index][1]]
                );

                index = Resources::triTable[caseID][i + 1];
                glm::vec3 v2 = Interpolate
                (
                    m_CornerPositions[Resources::sidesTable[index][0]],
                    m_CornerPositions[Resources::sidesTable[index][1]],
                    m_CornerDensityValues[Resources::sidesTable[index][0]],
                    m_CornerDensityValues[Resources::sidesTable[index][1]]
                );

                index = Resources::triTable[caseID][i + 2];
                glm::vec3 v3 = Interpolate
                (
                    m_CornerPositions[Resources::sidesTable[index][0]],
                    m_CornerPositions[Resources::sidesTable[index][1]],
                    m_CornerDensityValues[Resources::sidesTable[index][0]],
                    m_CornerDensityValues[Resources::sidesTable[index][1]]
                );

                glm::vec3 normal = glm::normalize(glm::cross(v2 - v1, v3 - v1));

                PushVertex(v1, normal);
                PushVertex(v2, normal);
                PushVertex(v3, normal);
            }
        }
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

    int Chunk::GetSampleID(glm::vec3 position)
    {
        return position.x + (position.y * m_Samples.x) + (position.z * m_Samples.x * m_Samples.y);
    }

    void Chunk::PushVertex(glm::vec3 vertex, glm::vec3 normal)
    {
        m_Vertices.push_back(vertex.x);
        m_Vertices.push_back(vertex.y);
        m_Vertices.push_back(vertex.z);
        m_Vertices.push_back(normal.x);
        m_Vertices.push_back(normal.y);
        m_Vertices.push_back(normal.z);
    }
}
