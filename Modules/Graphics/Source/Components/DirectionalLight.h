#pragma once
#include "../GraphicsExports.h"
#include <glm/glm.hpp>

namespace Forgex::Graphics::Components
{
    struct GRAPHICS_API DirectionalLight
    {
        glm::vec3 m_Color = glm::vec3(1.0f);
    };
}
