#pragma once
#include <ForgexCore.h>
#include "Components/VoxelChunk.h"
#include "VoxelExports.h"

#include "Utils/VoxelPipeline/SurfaceNoiseStep.h"
#include "Utils/VoxelPipeline/WormCaveStep.h"

namespace Forgex::Voxel
{
    class VOXEL_API VoxelSettings : public Core::Interfaces::ISettings
    {
    public:
        VoxelSettings()
        {
            m_VoxelPipeline.RegisterStep<Utils::TerrainSteps::SurfaceNoiseStep>(m_NoiseSeed);
            m_VoxelPipeline.RegisterStep<Utils::TerrainSteps::WormCaveStep>();
        }

        const Core::Pipeline<Components::Chunk>& GetVoxelPipeline() { return m_VoxelPipeline; }

    private:
        int m_NoiseSeed = 23523; //Hardcoded for now
        Core::Pipeline<Components::Chunk> m_VoxelPipeline;
    };
}
