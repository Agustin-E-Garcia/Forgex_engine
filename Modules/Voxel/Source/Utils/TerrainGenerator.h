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

        float GetNoiseAtXZ(float x, float z);
        int8_t GetDensityValueAtPoint(glm::vec3 position, float topHeight);
        int8_t GetDensityValueAtPoint(glm::vec3 position, float topHeight, float noise);

    private:
        int m_Seed;
        FastNoiseLite m_Noise;
    };
}
