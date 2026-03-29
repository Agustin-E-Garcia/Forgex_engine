#pragma once
#include "../Components/Transform.h"
#include "../Interfaces/ISystem.h"
#include "glm/common.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/quaternion_trigonometric.hpp"
#include "glm/fwd.hpp"
#include "glm/gtc/quaternion.hpp"

namespace Forgex::Core::Systems
{
    class TransformSystem : public Interfaces::PerEntitySystem<Components::Transform>
    {
        void OnUpdate(float deltaTime, const entt::entity& entity, Components::Transform& transform) override
        {
            if(!transform.m_Dirty) return;

            UpdateLocation(transform);
            UpdateRotation(transform);
            UpdateScale(transform);

            transform.m_ModelMatrix = transform.m_ScaleMatrix * transform.m_RotationMatrix * transform.m_LocationMatrix;
        }

        void UpdateLocation(Components::Transform& transform) 
        {
            transform.m_LocationMatrix = glm::translate(glm::mat4(1.0f), transform.m_Position);
        }

        void UpdateRotation(Components::Transform& transform)
        {
            glm::quat qX = glm::angleAxis(transform.m_Rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
            glm::quat qY = glm::angleAxis(transform.m_Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
            glm::quat qZ = glm::angleAxis(transform.m_Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

            transform.m_RotationQuat = qZ * qY * qX;
            transform.m_RotationMatrix = glm::mat4_cast(transform.m_RotationQuat);

            transform.m_Forward = glm::vec3(transform.m_RotationMatrix[2]);
            transform.m_Up = glm::vec3(transform.m_RotationMatrix[1]);
            transform.m_Right = glm::vec3(transform.m_RotationMatrix[0]);
        }

        void UpdateScale(Components::Transform& transform)
        {
            transform.m_ScaleMatrix = glm::scale(glm::mat4(1.0f), transform.m_Scale);
        }

         virtual const char* GetName() override { return "TransformSystem"; }
    };
}
