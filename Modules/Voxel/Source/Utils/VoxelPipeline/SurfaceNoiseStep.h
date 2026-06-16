#pragma once
#include <ForgexCore.h>
#include <FastNoiseLite.h>

namespace Forgex::Voxel::Components { class Chunk; }

namespace Forgex::Voxel::Utils::TerrainSteps
{
    class SurfaceNoiseStep : public Core::Interfaces::IPipelineStep<Components::Chunk>
    {
    public:
        SurfaceNoiseStep(int seed);
        void Execute(Components::Chunk& chunk) override;

    private:
        FastNoiseLite m_Noise;
    };
}
