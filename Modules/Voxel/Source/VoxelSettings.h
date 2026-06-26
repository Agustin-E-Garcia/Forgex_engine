#pragma once
#include <ForgexCore.h>
#include "Components/Chunk.h"
#include "VoxelExports.h"

#include "Utils/VoxelPipeline/SurfaceNoiseStep.h"

namespace Forgex::Voxel
{
    class VOXEL_API VoxelSettings : public Core::Interfaces::ISettings
    {
    public:
        VoxelSettings()
        {
            m_VoxelPipeline.RegisterStep<Utils::TerrainSteps::SurfaceNoiseStep>(m_NoiseSeed);
        }

        const Core::Pipeline<Components::ChunkData>& GetVoxelPipeline() const { return m_VoxelPipeline; }
        const glm::vec3 GetChunkSampleCount() const { return m_ChunkSampleCount; }
        const float GetChunkSampleDensity() const { return m_ChunkSampleDensity; }
        const float GetMapSurfaceCutoff() const { return m_SurfaceCutoff; }

    private:
        int m_NoiseSeed = 23523; //Hardcoded for now
        Core::Pipeline<Components::ChunkData> m_VoxelPipeline;

        glm::vec3 m_ChunkSampleCount = glm::vec3(64.0f);
        float m_ChunkSampleDensity = 1.0f;

        float m_SurfaceCutoff = 0;
    };
}
