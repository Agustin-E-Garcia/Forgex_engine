#include "VoxelMap.h"
#include <ForgexDebugTools.h>
#include <FastNoiseLite.h>

#include <chrono>

namespace Forgex::Voxel
{
    VoxelMap::VoxelMap()
    {
        glm::vec3 chunks = m_MapArea / m_ChunkSize;
        int chunkCount = chunks.x * chunks.y * chunks.z;

        m_Chunks.reserve(chunkCount);

        Chunk::s_SampleDensity = m_SampleDensity;
        Chunk::s_Cutoff = m_Cutoff;
        Chunk::s_NoiseSeed = 1337; // Hardcoded for now, eventually we'll be able to setup whichever seed we want
        Chunk::s_TopMapY = m_MapArea.y;

        auto start = std::chrono::high_resolution_clock::now();

        for(int z = 0; z < chunks.z; z++)
        for(int y = 0; y < chunks.y; y++)
        for(int x = 0; x < chunks.x; x++)
        {
            m_Chunks.emplace_back(glm::vec3(x, y, z), m_ChunkSize);
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        LOG_CORE(Debug::Info, "Took: " + std::to_string(duration.count()) + "ms");
    }

    VoxelMap::~VoxelMap() {}
}
