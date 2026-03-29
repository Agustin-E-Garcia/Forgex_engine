#pragma once
#include "../Components/Transform.h"
#include "../Interfaces/ISystem.h"

namespace Forgex::Core::Systems
{
    class TransformSystem : public Interfaces::PerEntitySystem<Components::Transform>
    {
        void OnUpdate(float deltaTime, const entt::entity& entity, Components::Transform& transform) override
        {
            if(!transform.m_Dirty) return;

            transform.m_LocationMatrix = glm::translate(glm::mat4(1.0f), transform.m_Position);

            transform.m_Forward        = glm::normalize(transform.m_RotationQuat * glm::vec3(0.0f, 0.0f, -1.0f));
            transform.m_Right          = glm::normalize(transform.m_RotationQuat * glm::vec3(1.0f, 0.0f, 0.0f));
            transform.m_RotationMatrix = glm::mat4_cast(transform.m_RotationQuat);

            // Recalculate scale matrix

            transform.m_ModelMatrix = transform.m_ScaleMatrix * transform.m_RotationMatrix * transform.m_LocationMatrix;
        }
         virtual const char* GetName() override { return "TransformSystem"; }
    };
}
