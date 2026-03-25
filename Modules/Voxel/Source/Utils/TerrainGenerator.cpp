#include "TerrainGenerator.h"

namespace Forgex::Voxel::Utils
{
    TerrainGenerator::TerrainGenerator(int seed) : m_Seed(seed)
    {
        m_Noise.SetSeed(m_Seed);
        m_Noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
        m_Noise.SetFractalType(FastNoiseLite::FractalType_FBm);
    }
    TerrainGenerator::~TerrainGenerator() {}

    uint8_t TerrainGenerator::GetDensityValueAtPoint(glm::vec3 position, float topHeight, float* surfaceHeight)
    {
        float n = m_Noise.GetNoise(position.x, position.z);
        *surfaceHeight = (n + 1.0f) / 2.0f * topHeight;
        float density = (*surfaceHeight - position.y) / topHeight * 255.0f;
        return glm::clamp(density + 127.0f, 0.0f, 255.0f);
    }
}
