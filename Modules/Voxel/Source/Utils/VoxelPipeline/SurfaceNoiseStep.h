#pragma once
#include <ForgexCore.h>
#include <FastNoiseLite.h>
#include "../../VoxelExports.h"

namespace Forgex::Voxel::Components { struct ChunkData; }

namespace Forgex::Voxel::Utils::TerrainSteps
{
    class VOXEL_API SurfaceNoiseStep : public Core::Interfaces::IPipelineStep<Components::ChunkData>
    {
    public:
        SurfaceNoiseStep(int seed);
        void Execute(Components::ChunkData& chunk) override;

    private:
        FastNoiseLite m_Noise;
    };
}
