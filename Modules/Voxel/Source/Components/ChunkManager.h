#pragma once
#include "../VoxelExports.h"
#include <ForgexCore.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>
#include <unordered_map>

namespace Forgex::Voxel::Components
{
    struct VOXEL_API ChunkManager
    {
        entt::entity m_CenterEntity;
        int m_ViewRange = 16;

        std::unordered_map<glm::vec3, entt::entity> m_ChunkEntityCollection;
    };
}
