#pragma once
#include <glm/glm.hpp>

namespace Forgex::Graphics::Components
{
    struct PointLight
    {
        glm::vec3 color = glm::vec3(1.0f);
        float radius = 10.0f;
        float intensity = 0.5f;
    };
}
