#pragma once
#include <glm/glm.hpp>

namespace Forgex::Scene 
{
    struct Camera
    {
        bool m_IsActiveCamera = true;
        float m_FieldOfView = 80.0f;
        glm::vec2 m_AspectRatio = glm::vec2(4, 3);
        float m_NearPlane = 0.1f;
        float m_FarPlane = 1000.0f;
    };
}
