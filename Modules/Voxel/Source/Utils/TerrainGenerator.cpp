#include "TerrainGenerator.h"

namespace Forgex::Voxel::Utils
{
    TerrainGenerator::TerrainGenerator(int seed) : m_Seed(seed)
    {
        m_Noise.SetSeed(m_Seed);
        m_Noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
        m_Noise.SetFractalType(FastNoiseLite::FractalType_FBm);
        m_Noise.SetFrequency(0.003f);
    }
    TerrainGenerator::~TerrainGenerator() {}

    float TerrainGenerator::GetNoiseAtXZ(float x, float z)
    {
        return m_Noise.GetNoise(x, z);
    }

    int8_t TerrainGenerator::GetDensityValueAtPoint(glm::vec3 position, float topHeight, float noise)
    {
        topHeight = 127;

        //float noise = m_Noise.GetNoise(position.x, position.z);
        //float normalizedNoise = (noise + 1.0f) * 0.5f;

        float curve = glm::pow(noise, 2.0f);

        float density = -position.y + curve * topHeight;
        return glm::clamp(density, -128.0f, 127.0f);
    }
}
