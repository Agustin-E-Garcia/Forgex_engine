#pragma once
#include <future>
#include <glm/glm.hpp>
#include <vector>
#include <ForgexGraphics.h>

namespace Forgex::Voxel::Components
{
    struct ChunkData
    {
        glm::vec3 m_MapPosition = glm::vec3(0.0f);
        std::vector<int8_t> m_DensityValues;
    };

    struct Chunk
    {
        ChunkData m_Data;

        bool m_IsDirty = false;
        std::future<ChunkData> m_DensityFuture;
        std::future<Graphics::MeshData> m_MeshingFuture;
    };
}
