#pragma once
#include "VoxelChunk.h"
#include <glm/glm.hpp>
#include <vector>

namespace Forgex::Voxel::Components
{
    struct VoxelMap
    {
        glm::vec3 m_MapArea = glm::vec3(256.0f);
        glm::vec3 m_ChunkSize = glm::vec3(32.0f);
        float m_SampleDensity = 1.0f;
        int m_Cutoff = 0;

        int m_Seed = 1332;

        std::vector<const Chunk*> m_Chunks;
    };
}
