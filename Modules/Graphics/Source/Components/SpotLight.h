#pragma once
#include <glm/glm.hpp>

namespace Forgex::Graphics::Components
{
    struct SpotLight
    {
        glm::vec3 m_Color = glm::vec3(1.0f);
        float m_CutOff = glm::cos(glm::radians(12.5f));
    };
}
