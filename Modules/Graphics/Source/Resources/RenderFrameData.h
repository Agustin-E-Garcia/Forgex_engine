#pragma once
#include <glm/glm.hpp>
#include "../Components/PointLight.h"
#include "../Components/DirectionalLight.h"
#include "../Components/SpotLight.h"
#include "glm/fwd.hpp"

namespace Forgex::Graphics::Resources
{

    struct DirectionalLightData
    {
        glm::vec4 m_Direction = glm::vec4(0.0f);
        glm::vec4 m_Color = glm::vec4(1.0f);

        DirectionalLightData() = default;
        DirectionalLightData(const Components::DirectionalLight& light, glm::vec3 direction) :
            m_Direction(glm::vec4(direction, 1.0f)), m_Color(glm::vec4(light.m_Color, 1.0f)) {}
    };

    struct PointLightData
    {
        glm::vec3 m_Position = glm::vec3(0.0f);
        float m_Constant = 0.0f;
        glm::vec3 m_Color = glm::vec3(1.0f);
        float m_Linear = 0.0f;
        float m_Quadratic = 0.0f;

        PointLightData() = default;
        PointLightData(const Components::PointLight& light, glm::vec3 worldPos) :
            m_Position(worldPos), m_Constant(light.m_Constant), m_Color(light.m_Color), m_Linear(light.m_Linear), m_Quadratic(light.m_Quadratic) {}
    };

    struct SpotLightData
    {
        glm::vec4 m_Position = glm::vec4(0.0f);
        glm::vec3 m_Direction = glm::vec3(0.0f);
        float m_CutOff;
        glm::vec4 m_Color = glm::vec4(1.0f);

        SpotLightData() = default;
        SpotLightData(const Components::SpotLight& light, glm::vec3 worldPos, glm::vec3 direction) :
            m_Position(glm::vec4(worldPos, 1.0f)), m_Direction(direction), m_CutOff(light.m_CutOff), m_Color(glm::vec4(light.m_Color, 1.0f)) {}
    };

    struct RenderFrameData
    {
        glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
        glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
        glm::vec4 m_CameraPosition = glm::vec4(0.0f);
        float m_Time = 0;

        int m_DirectionalLightsCount = 0;
        int m_PointLightsCount = 0;
        int m_SpotLightsCount = 0;

        DirectionalLightData m_DirectionalLights[5];
        PointLightData m_PointLights[5];
        SpotLightData m_SpotLights[5];
    };
}
