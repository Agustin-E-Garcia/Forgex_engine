#pragma once
#include <glm/glm.hpp>

namespace Forgex::Graphics::Resources
{
    struct RenderView
    {
        glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
        glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
    };
}
