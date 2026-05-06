#pragma once
#include "../GraphicsExports.h"
#include <glm/glm.hpp>

namespace Forgex::Graphics::Components
{
    struct GRAPHICS_API PointLight
    {
        glm::vec3 m_Color = glm::vec3(1.0f);

        float m_Constant = 1.0f;
        float m_Linear = 0.09f;
        float m_Quadratic = 0.032f;
    };
}
