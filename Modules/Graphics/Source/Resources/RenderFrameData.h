#pragma once
#include <glm/glm.hpp>
#include "../Components/PointLight.h"

namespace Forgex::Graphics::Resources
{
    struct LightData
    {
        const Components::PointLight& m_Light;
        const glm::vec3 m_WorldPosition;
    };

    struct RenderFrameData
    {
        glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
        glm::mat4 m_ViewMatrix = glm::mat4(1.0f);

        std::vector<LightData> m_Lights;
    };
}
