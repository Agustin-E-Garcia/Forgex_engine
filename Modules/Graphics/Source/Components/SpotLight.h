#pragma once
#include "../GraphicsExports.h"
#include <glm/glm.hpp>

namespace Forgex::Graphics::Components
{
    struct GRAPHICS_API SpotLight
    {
        glm::vec3 m_Color = glm::vec3(1.0f);
        float m_CutOff = 12.5f;
        float m_OuterCutOff = 17.5f;
    };
}
