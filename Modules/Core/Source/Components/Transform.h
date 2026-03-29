#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Forgex::Core::Components
{
    struct Transform
    {
        glm::vec3 m_Position = glm::vec3(0.0f);
        glm::vec3 m_Rotation = glm::vec3(0.0f);
        glm::vec3 m_Scale = glm::vec3(1.0f);

        glm::vec3 m_Forward = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 m_Right = glm::vec3(1.0f, 0.0f, 0.0f);
        glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);

        glm::quat m_RotationQuat = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);

        glm::mat4 m_ModelMatrix = glm::mat4(1.0f);
        glm::mat4 m_LocationMatrix = glm::mat4(1.0f);
        glm::mat4 m_ScaleMatrix = glm::mat4(1.0f);
        glm::mat4 m_RotationMatrix = glm::mat4(1.0f);

        bool m_Dirty = false;
    };
}
