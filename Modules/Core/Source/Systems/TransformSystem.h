#pragma once
#include "../Components/Transform.h"
#include "../Interfaces/ISystem.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "glm/gtc/quaternion.hpp"

namespace Forgex::Core::Systems
{
    class TransformSystem : public Interfaces::PerEntitySystem<Components::Transform>
    {
        void OnUpdate(float deltatime, const entt::entity& entity, Components::Transform& transform) override
        {
            if(!transform.m_Dirty) return;

            updatelocation(transform);
            updaterotation(transform);
            updatescale(transform);

            transform.m_ModelMatrix = transform.m_LocationMatrix * transform.m_RotationMatrix * transform.m_ScaleMatrix;

            transform.m_Dirty = false;
        }

        void updatelocation(Components::Transform& transform)
        {
            transform.m_LocationMatrix = glm::translate(glm::mat4(1.0f), transform.m_Position);
        }

        void updaterotation(Components::Transform& transform)
        {
            glm::vec3 radians = glm::radians(transform.m_Rotation);
            glm::quat qx = glm::angleAxis(radians.x, glm::vec3(1.0f, 0.0f, 0.0f));
            glm::quat qy = glm::angleAxis(radians.y, glm::vec3(0.0f, 1.0f, 0.0f));
            glm::quat qz = glm::angleAxis(radians.z, glm::vec3(0.0f, 0.0f, 1.0f));

            transform.m_RotationQuat = qz * qy * qx;
            transform.m_RotationMatrix = glm::mat4_cast(transform.m_RotationQuat);

            transform.m_Forward = glm::vec3(transform.m_RotationMatrix[2]);
            transform.m_Up = glm::vec3(transform.m_RotationMatrix[1]);
            transform.m_Right = glm::vec3(transform.m_RotationMatrix[0]);
        }

        void updatescale(Components::Transform& transform)
        {
            transform.m_ScaleMatrix = glm::scale(glm::mat4(1.0f), transform.m_Scale);
        }

         virtual const char* GetName() override { return "TransformSystem"; }
    };
}
