#pragma once
#include <glm/glm.hpp>
#include <FastNoiseLite.h>

namespace Forgex::Voxel::Utils
{
    class TerrainGenerator
    {
    public:
        TerrainGenerator(int seed);
        ~TerrainGenerator();

        uint8_t GetDensityValueAtPoint(glm::vec3 position, float topHeight, float* surfaceHeight);

    private:
        int m_Seed;
        FastNoiseLite m_Noise;
    };
}
