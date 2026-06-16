#pragma once
#include <ForgexCore.h>
#include <vector>
#include <glm/glm.hpp>
#include "../../VoxelExports.h"

namespace Forgex::Voxel::Components { class Chunk; }

namespace Forgex::Voxel::Utils::TerrainSteps
{
    struct WormPathNode
    {
        glm::vec3 m_WorldPosition;
        float m_Radius;
    };

    class VOXEL_API WormCaveStep : public Core::Interfaces::IPipelineStep<Components::Chunk>
    {
    public:
        WormCaveStep();
        void Execute(Components::Chunk& chunk) override;

    private:
        std::vector<std::vector<WormPathNode>> m_WormPath;
    };
}
