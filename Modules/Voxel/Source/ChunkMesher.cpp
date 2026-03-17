#include "ChunkMesher.h"
#include "Resources/MarchingCubesTable.h"

namespace Forgex::Voxel
{
    ChunkMesher::ChunkMesher(Chunk* chunk, TerrainGenerator* generator) : m_Chunk(chunk), m_Generator(generator) {}
    ChunkMesher::~ChunkMesher() {}

    void ChunkMesher::GenerateMesh()
    {
        m_Chunk->m_Vertices.clear();
        m_Chunk->m_Indices.clear();

        m_Chunk->m_Vertices.reserve(m_Chunk->m_Samples.x * m_Chunk->m_Samples.y * m_Chunk->m_Samples.z * 5 * 3 * 6);
        for (int z = 0; z < (int)m_Chunk->m_Samples.z - 1; z++)
        for (int y = 0; y < (int)m_Chunk->m_Samples.y - 1; y++)
        for (int x = 0; x < (int)m_Chunk->m_Samples.x - 1; x++)
        {
            // We need the vectors to adhere to this order:
            //    4----5
            //   /|   /|
            //  7----6 |
            //  | 0--|-1
            //  |/   |/
            //  3----2

            glm::vec3 cornerPositions[8] =
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

            int cornerDensityValues[8] = 
            {
                m_Chunk->m_DensityValues[GetSampleID(cornerPositions[0])], // 0
                m_Chunk->m_DensityValues[GetSampleID(cornerPositions[1])], // 1
                m_Chunk->m_DensityValues[GetSampleID(cornerPositions[2])], // 2
                m_Chunk->m_DensityValues[GetSampleID(cornerPositions[3])], // 3
                m_Chunk->m_DensityValues[GetSampleID(cornerPositions[4])], // 4
                m_Chunk->m_DensityValues[GetSampleID(cornerPositions[5])], // 5
                m_Chunk->m_DensityValues[GetSampleID(cornerPositions[6])], // 6
                m_Chunk->m_DensityValues[GetSampleID(cornerPositions[7])], // 7
            };

            int caseID = 0;
            for (int i = 0; i < 8; i++)
            {
                if(cornerDensityValues[i] < m_Chunk->m_Cutoff) continue;
                caseID |= (1 << i);
            }

            if(caseID == 0 || caseID == 255) continue; // if no sample is over cutoff, then we skip this cube

            for (int i = 0; i < 16; i += 3)
            {
                if(Resources::triTable[caseID][i] == -1) break;

                int index = Resources::triTable[caseID][i];
                int index_v1 = GetOrAddVertexIndex
                    (
                        cornerPositions[Resources::sidesTable[index][0]],
                        cornerPositions[Resources::sidesTable[index][1]]
                    );

                index = Resources::triTable[caseID][i + 1];
                int index_v2 = GetOrAddVertexIndex
                    (
                        cornerPositions[Resources::sidesTable[index][0]],
                        cornerPositions[Resources::sidesTable[index][1]]
                    );

                index = Resources::triTable[caseID][i + 2];
                int index_v3 = GetOrAddVertexIndex
                    (
                        cornerPositions[Resources::sidesTable[index][0]],
                        cornerPositions[Resources::sidesTable[index][1]]
                    );

                m_Chunk->m_Indices.push_back(index_v1);
                m_Chunk->m_Indices.push_back(index_v2);
                m_Chunk->m_Indices.push_back(index_v3);
           }
        }
    }

    uint32_t ChunkMesher::GetOrAddVertexIndex(glm::vec3 posA, glm::vec3 posB)
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

        glm::vec3 vertex = Interpolate(posA, posB, m_Chunk->m_DensityValues[idA], m_Chunk->m_DensityValues[idB]);
        glm::vec3 normal = CalculateSampleGradientNormal(vertex);
        uint32_t vertexIndex = PushVertex(vertex * m_Chunk->m_SampleDensity, normal);
        m_VertexToIndexMap[mapKey] = vertexIndex;

        return vertexIndex;
    }

    glm::vec3 ChunkMesher::CalculateSampleGradientNormal(glm::vec3 vertexLocalPos)
    {
        glm::vec3 worldPos = (m_Chunk->m_Position * m_Chunk->m_Size) + (vertexLocalPos * m_Chunk->m_SampleDensity);
        float delta = 0.5f;
        float surfaceHeight;

        float dx = m_Generator->GetDensityValueAtPoint
            (
                worldPos + 
                glm::vec3(delta, 0, 0), m_Chunk->m_Size.y, &surfaceHeight) -
                m_Generator->GetDensityValueAtPoint(worldPos - glm::vec3(delta, 0, 0), m_Chunk->m_Size.y, &surfaceHeight
            );
        float dy = m_Generator->GetDensityValueAtPoint
            (
                worldPos + 
                glm::vec3(0, delta, 0), m_Chunk->m_Size.y, &surfaceHeight) -
                m_Generator->GetDensityValueAtPoint(worldPos - glm::vec3(0, delta, 0), m_Chunk->m_Size.y, &surfaceHeight
            );
        float dz = m_Generator->GetDensityValueAtPoint
            (
                worldPos + 
                glm::vec3(0, 0, delta), m_Chunk->m_Size.y, &surfaceHeight) -
                m_Generator->GetDensityValueAtPoint(worldPos - glm::vec3(0, 0, delta), m_Chunk->m_Size.y, &surfaceHeight
            );

        return glm::normalize(-glm::vec3(dx, dy, dz));
    }

    glm::vec3 ChunkMesher::Interpolate(glm::vec3 posA, glm::vec3 posB, uint8_t valA, uint8_t valB)
    {
        float t = (m_Chunk->m_Cutoff - valA) / (float)(valB - valA);
        return posA + t * (posB - posA);
    }

    uint64_t ChunkMesher::GetSampleID(glm::vec3 position)
    {
        return position.x + (position.y * m_Chunk->m_Samples.x) + (position.z * m_Chunk->m_Samples.x * m_Chunk->m_Samples.y);
    }

    uint32_t ChunkMesher::PushVertex(glm::vec3 vertex, glm::vec3 normal)
    {
        uint32_t index = m_Chunk->m_Vertices.size() / 6;
        // Add Vertex
        m_Chunk->m_Vertices.push_back(vertex.x);
        m_Chunk->m_Vertices.push_back(vertex.y);
        m_Chunk->m_Vertices.push_back(vertex.z);
        // Add Normal
        m_Chunk->m_Vertices.push_back(normal.x);
        m_Chunk->m_Vertices.push_back(normal.y);
        m_Chunk->m_Vertices.push_back(normal.z);

        return index;
    }
}
