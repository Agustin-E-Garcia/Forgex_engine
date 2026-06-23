#include "SurfaceNoiseStep.h"
#include "../../Components/Chunk.h"
#include "../../VoxelSettings.h"

namespace Forgex::Voxel::Utils::TerrainSteps
{
    int8_t GetDensityValueAtPoint(glm::vec3 position, float topHeight, float noise)
    {
        float surfaceHeight = 0 + (noise * topHeight);

        return position.y < surfaceHeight ? (int8_t)255 : 0;
    }

    SurfaceNoiseStep::SurfaceNoiseStep(int seed)
    {
        m_Noise.SetSeed(seed);
        m_Noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
        m_Noise.SetFractalType(FastNoiseLite::FractalType_FBm);
        m_Noise.SetFrequency(0.003f);
    }

    void SurfaceNoiseStep::Execute(Components::ChunkData& chunk)
    {
        const VoxelSettings* settings = GET_SERVICE(Core::Settings::ProjectSettings)->GetSettings<VoxelSettings>();
        glm::vec3 worldOffset = chunk.m_MapPosition * settings->GetChunkSampleCount();
        glm::vec3 samples = settings->GetChunkSampleCount() + glm::vec3(2.0f);

        for(int z = 0; z < samples.z; z++)
        for(int x = 0; x < samples.x; x++)
        {
            float noiseValue = m_Noise.GetNoise(worldOffset.x + x * settings->GetChunkSampleDensity(), worldOffset.z + z * settings->GetChunkSampleDensity());
            noiseValue = (noiseValue + 1) * 0.5f;

            for(int y = 0; y < samples.y; y++)
            {
                glm::vec3 worldPosition = worldOffset + glm::vec3(x, y, z) * settings->GetChunkSampleDensity();
                float surfaceHeight = 0 + (noiseValue * 30); // 30 is top height

                chunk.m_DensityValues.push_back(worldPosition.y < surfaceHeight ? (int8_t)255 : 0); // if under the surface, then it's solid, else it's air
            }
        }
    }
}
