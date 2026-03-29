#pragma once
#include <glm/glm.hpp>
#include "../Components/PointLight.h"

namespace Forgex::Graphics::Resources
{
    struct LightData
    {
        glm::vec3 m_Position = glm::vec3(0.0f);
        float m_Intensity = 1.0f;
        glm::vec3 m_Color = glm::vec3(1.0f);
        float m_Radius = 80.0f;

        LightData() = default;
        LightData(const Components::PointLight& light, glm::vec3 worldPos) :
            m_Position(worldPos), m_Intensity(light.m_Intensity), m_Color(light.m_Color), m_Radius(light.m_Radius) {}
    };

    struct RenderFrameData
    {
        glm::mat4 m_ViewMatrix = glm::mat4(1.0f);   // 64 bytes
        glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);   // 64 bytes
        glm::vec3 m_CameraPosition = glm::vec3(0.0f);   // 12 bytes
        float m_Time = 0;                               // 4 bytes -> fills out the vec4 (16 bytes)
        LightData m_Lights[16];                         // 32 bytes * 16
        int m_LightCount = 0;                           // 4 bytes
    };
}
