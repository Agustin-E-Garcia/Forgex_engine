#pragma once
#include <glm/glm.hpp>

namespace Forgex::Scene
{
    struct Speed
    {
        glm::vec3 m_MoveSpeed = glm::vec3(1.0f, 0.0f, 0.0f);
        glm::vec3 m_RotateSpeed = glm::vec3(0.0f, 0.0f, 0.0f);
    };
}
