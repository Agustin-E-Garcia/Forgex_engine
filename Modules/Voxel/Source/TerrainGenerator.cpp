#include "TerrainGenerator.h"
#include <FastNoiseLite.h>

namespace Forgex::Voxel
{
    TerrainGenerator::TerrainGenerator(int seed) : m_Seed(seed) {}
    TerrainGenerator::~TerrainGenerator() {}

    uint8_t TerrainGenerator::GetDensityValueAtPoint(glm::vec3 position, float topHeight, float* surfaceHeight)
    {
        FastNoiseLite noise;
        noise.SetSeed(m_Seed);
        noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
        noise.SetFractalType(FastNoiseLite::FractalType_FBm);

        float n = noise.GetNoise(position.x, position.z);
        *surfaceHeight = (n + 1.0f) / 2.0f * topHeight;
        float density = (*surfaceHeight - position.y) / topHeight * 255.0f;
        return glm::clamp(density + 127.0f, 0.0f, 255.0f);
    }
}
