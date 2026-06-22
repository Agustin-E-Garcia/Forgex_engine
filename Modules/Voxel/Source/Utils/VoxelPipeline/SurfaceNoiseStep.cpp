#include "SurfaceNoiseStep.h"
#include "../../Components/VoxelChunk.h"

namespace Forgex::Voxel::Utils::TerrainSteps
{
    int8_t GetDensityValueAtPoint(glm::vec3 position, float topHeight, float noise)
    {
        topHeight = 127;

        //float noise = m_Noise.GetNoise(position.x, position.z);
        //float normalizedNoise = (noise + 1.0f) * 0.5f;

        float curve = glm::pow(noise, 2.0f);

        float density = -position.y + curve * topHeight;
        return glm::clamp(density, -128.0f, 127.0f);
    }

    SurfaceNoiseStep::SurfaceNoiseStep(int seed)
    {
        m_Noise.SetSeed(seed);
        m_Noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
        m_Noise.SetFractalType(FastNoiseLite::FractalType_FBm);
        m_Noise.SetFrequency(0.003f);
    }

    void SurfaceNoiseStep::Execute(Components::Chunk& chunk) 
    {
        glm::vec3 worldOffset = chunk.m_Position * chunk.m_Size;

        for(int z = 0; z < chunk.m_Samples.z; z++)
        for(int x = 0; x < chunk.m_Samples.x; x++)
        {
            float noiseValue = m_Noise.GetNoise(worldOffset.x + x * chunk.m_SampleDensity, worldOffset.z + z * chunk.m_SampleDensity);

            for(int y = 0; y < chunk.m_Samples.y; y++)
            {
                glm::vec3 worldPosition = worldOffset + glm::vec3(x, y, z) * chunk.m_SampleDensity;
                chunk.m_DensityValues.push_back(GetDensityValueAtPoint(worldPosition, 127, noiseValue));
            }
        }
    }
}
