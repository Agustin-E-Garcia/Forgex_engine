#include "ChunkMesher.h"
#include "../VoxelSettings.h"
#include "../Resources/MarchingCubesTable.h"

#include <ForgexCore.h>
#include <vector>

namespace Forgex::Voxel::Utils
{
    ChunkMesher::ChunkMesher(const Components::ChunkData& chunk) : m_Chunk(chunk)
    {
        m_Samples = GET_SERVICE(Core::Settings::ProjectSettings)->GetSettings<VoxelSettings>()->GetChunkSampleCount() + glm::vec3(2.0f);
    }
    ChunkMesher::~ChunkMesher() {}

    void ChunkMesher::GenerateMesh(std::vector<float>& vertices, std::vector<int>& indices)
    {
        const VoxelSettings* settings = GET_SERVICE(Core::Settings::ProjectSettings)->GetSettings<VoxelSettings>();

        // We calculate the worst case upper bound
        // - 5: max number of triangles per cube
        // - 3: vertices per triangle
        // - 8: floats per vertex (3 position, 3 normal, 2 uv)
        vertices.reserve(m_Samples.x * m_Samples.y * m_Samples.z * 5 * 3 * 8);

        for (int z = 1; z < (int)m_Samples.z - 1; z++)
        for (int x = 1; x < (int)m_Samples.x - 1; x++)
        for (int y = 1; y < (int)m_Samples.y - 1; y++)
        {
            // We need the vectors to adhere to this order:
            //    4----5
            //   /|   /|
            //  7----6 |
            //  | 0--|-1
            //  |/   |/
            //  3----2

            int lx = x - 1, ly = y - 1, lz = z - 1;
            glm::vec3 cornerPositions[8] =
            {
                glm::vec3(lx    , ly    , lz + 1), // 0
                glm::vec3(lx + 1, ly    , lz + 1), // 1
                glm::vec3(lx + 1, ly    , lz    ), // 2
                glm::vec3(lx    , ly    , lz    ), // 3
                glm::vec3(lx    , ly + 1, lz + 1), // 4
                glm::vec3(lx + 1, ly + 1, lz + 1), // 5
                glm::vec3(lx + 1, ly + 1, lz    ), // 6
                glm::vec3(lx    , ly + 1, lz    ), // 7
            };

            int cornerDensityValues[8] = 
            {
                m_Chunk.m_DensityValues[GetSampleID(cornerPositions[0])], // 0
                m_Chunk.m_DensityValues[GetSampleID(cornerPositions[1])], // 1
                m_Chunk.m_DensityValues[GetSampleID(cornerPositions[2])], // 2
                m_Chunk.m_DensityValues[GetSampleID(cornerPositions[3])], // 3
                m_Chunk.m_DensityValues[GetSampleID(cornerPositions[4])], // 4
                m_Chunk.m_DensityValues[GetSampleID(cornerPositions[5])], // 5
                m_Chunk.m_DensityValues[GetSampleID(cornerPositions[6])], // 6
                m_Chunk.m_DensityValues[GetSampleID(cornerPositions[7])], // 7
            };

            int caseID = 0;
            for (int i = 0; i < 8; i++)
            {
                if(cornerDensityValues[i] < settings->GetMapSurfaceCutoff()) continue;
                caseID |= (1 << i);
            }

            if(caseID == 0 || caseID == 255) continue; // if no sample is over cutoff, then we skip this cube

            for (int i = 0; i < 16; i += 3)
            {
                if(Resources::triTable[caseID][i] == -1) break;

                int index = Resources::triTable[caseID][i];
                int index_v1 = GetOrAddVertexIndex
                    (
                        vertices,
                        cornerPositions[Resources::sidesTable[index][0]],
                        cornerPositions[Resources::sidesTable[index][1]]
                    );

                index = Resources::triTable[caseID][i + 1];
                int index_v2 = GetOrAddVertexIndex
                    (
                        vertices,
                        cornerPositions[Resources::sidesTable[index][0]],
                        cornerPositions[Resources::sidesTable[index][1]]
                    );

                index = Resources::triTable[caseID][i + 2];
                int index_v3 = GetOrAddVertexIndex
                    (
                        vertices,
                        cornerPositions[Resources::sidesTable[index][0]],
                        cornerPositions[Resources::sidesTable[index][1]]
                    );

                indices.push_back(index_v1);
                indices.push_back(index_v2);
                indices.push_back(index_v3);
           }
        }
    }

    uint32_t ChunkMesher::GetOrAddVertexIndex(std::vector<float>& vertices, glm::vec3 posA, glm::vec3 posB)
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

        glm::vec3 vertex = Interpolate(posA, posB, m_Chunk.m_DensityValues[idA], m_Chunk.m_DensityValues[idB]);
        glm::vec3 normal = CalculateSampleGradientNormal(vertex);
        uint32_t vertexIndex = PushVertex(vertices, vertex * GET_SERVICE(Core::Settings::ProjectSettings)->GetSettings<VoxelSettings>()->GetChunkSampleDensity(), normal);
        m_VertexToIndexMap[mapKey] = vertexIndex;

        return vertexIndex;
    }

    // TODO: Claude wrote this, for now I leave it to test other stuff, but I need to still check this code and make sure I understand what's happening here
    glm::vec3 ChunkMesher::CalculateSampleGradientNormal(glm::vec3 vertexLocalPos)
    {
        // Central differences over the chunk's density grid. The vertex usually sits between
        // samples, so we trilinearly interpolate the density field at each offset.
        float dx = SampleDensity(vertexLocalPos + glm::vec3(1, 0, 0)) - SampleDensity(vertexLocalPos - glm::vec3(1, 0, 0));
        float dy = SampleDensity(vertexLocalPos + glm::vec3(0, 1, 0)) - SampleDensity(vertexLocalPos - glm::vec3(0, 1, 0));
        float dz = SampleDensity(vertexLocalPos + glm::vec3(0, 0, 1)) - SampleDensity(vertexLocalPos - glm::vec3(0, 0, 1));

        return glm::normalize(-glm::vec3(dx, dy, dz));
    }

    float ChunkMesher::SampleDensity(glm::vec3 localPos)
    {
        // Clamp to the valid sample range so neighbour lookups never go out of bounds.
        glm::vec3 maxPos = glm::vec3(m_Samples) - glm::vec3(1.0f);
        localPos = glm::clamp(localPos, glm::vec3(0.0f), maxPos);

        glm::ivec3 p0 = glm::ivec3(glm::floor(localPos));
        glm::ivec3 p1 = glm::min(p0 + 1, glm::ivec3(maxPos));
        glm::vec3 f = localPos - glm::vec3(p0);

        auto d = [&](int x, int y, int z)
        {
            return (float)m_Chunk.m_DensityValues[GetSampleID(glm::vec3(x, y, z))];
        };

        // Trilinear interpolation between the eight surrounding samples.
        float c00 = glm::mix(d(p0.x, p0.y, p0.z), d(p1.x, p0.y, p0.z), f.x);
        float c10 = glm::mix(d(p0.x, p1.y, p0.z), d(p1.x, p1.y, p0.z), f.x);
        float c01 = glm::mix(d(p0.x, p0.y, p1.z), d(p1.x, p0.y, p1.z), f.x);
        float c11 = glm::mix(d(p0.x, p1.y, p1.z), d(p1.x, p1.y, p1.z), f.x);

        float c0 = glm::mix(c00, c10, f.y);
        float c1 = glm::mix(c01, c11, f.y);

        return glm::mix(c0, c1, f.z);
    }
    // TODO

    glm::vec3 ChunkMesher::Interpolate(glm::vec3 posA, glm::vec3 posB, int8_t valA, int8_t valB)
    {
        float t = (GET_SERVICE(Core::Settings::ProjectSettings)->GetSettings<VoxelSettings>()->GetMapSurfaceCutoff() - valA) / (float)(valB - valA);
        return posA + t * (posB - posA);
    }

    uint64_t ChunkMesher::GetSampleID(glm::vec3 position)
    {
        return position.y + (position.x * m_Samples.y) + (position.z * m_Samples.y * m_Samples.x);
    }

    uint32_t ChunkMesher::PushVertex(std::vector<float>& vertices, glm::vec3 vertex, glm::vec3 normal)
    {
        uint32_t index = vertices.size() / 8;
        // Add Vertex
        vertices.push_back(vertex.x);
        vertices.push_back(vertex.y);
        vertices.push_back(vertex.z);
        // Add Normal
        vertices.push_back(normal.x);
        vertices.push_back(normal.y);
        vertices.push_back(normal.z);
        // Add UVs
        vertices.push_back(0.0f);
        vertices.push_back(0.0f);

        return index;
    }
}
