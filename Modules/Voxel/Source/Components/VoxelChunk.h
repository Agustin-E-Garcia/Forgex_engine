#pragma once
#include <future>
#include <glm/glm.hpp>
#include <vector>
#include <ForgexGraphics.h>

namespace Forgex::Voxel::Components
{
    struct Chunk
    {
        glm::vec3 m_Position = glm::vec3(0.0f);
        glm::vec3 m_Size = glm::vec3(64.0f);
        float m_SampleDensity = 1.0f;
        float m_Cutoff = 127;
        int m_NoiseSeed = 23523;

        glm::ivec3 m_Samples = glm::vec3(-10.f);
        std::vector<int8_t> m_DensityValues;

        bool m_IsDirty = true;
        std::future<std::vector<int8_t>> m_DensityFuture;
        std::future<Graphics::MeshData> m_MeshingFuture;
    };
}
