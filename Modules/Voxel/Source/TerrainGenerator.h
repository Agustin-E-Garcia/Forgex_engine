#pragma once
#include "VoxelExports.h"
#include <glm/glm.hpp>

namespace Forgex::Voxel
{
    class VOXEL_API TerrainGenerator
    {
    public:
        TerrainGenerator(int seed);
        ~TerrainGenerator();

        uint8_t GetDensityValueAtPoint(glm::vec3 position, float topHeight, float* surfaceHeight);

    private:
        int m_Seed;
    };
}
