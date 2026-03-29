#pragma once
#include <glm/glm.hpp>

namespace Forgex::Graphics::Components
{
    struct PointLight
    {
        glm::vec3 m_Color = glm::vec3(1.0f);
        float m_Radius = 10.0f;
        float m_Intensity = 0.5f;
    };
}
