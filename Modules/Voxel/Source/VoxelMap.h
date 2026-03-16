#pragma once
#include "VoxelExports.h"
#include "VoxelChunk.h"
#include <glm/glm.hpp>
#include <vector>

namespace Forgex::Voxel
{
    class VOXEL_API VoxelMap
    {
    public:
        VoxelMap();
        ~VoxelMap();

        std::vector<Chunk>::iterator begin() { return m_Chunks.begin(); }
        std::vector<Chunk>::iterator end() { return m_Chunks.end(); }

    private:
        glm::vec3 m_MapArea = glm::vec3(256.0f);
        glm::vec3 m_ChunkSize = glm::vec3(32.0f);
        float m_SampleDensity = 1.0f;
        int m_Cutoff = 127;

        std::vector<Chunk> m_Chunks;
    };
}
