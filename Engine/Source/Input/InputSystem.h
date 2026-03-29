#pragma once
#include <ForgexCore.h>
#include <ForgexGraphics.h>
#include <glm/gtc/matrix_transform.hpp>
#include "PlayerInput.h"
#include "InputManager.h"

namespace Forgex::Engine::Input
{
    class InputSystem : public Core::Interfaces::PerEntitySystem<Core::Components::Transform, PlayerInput>
    {
    public:
        void OnUpdate(float deltaTime, const entt::entity &entity, Core::Components::Transform& transform, PlayerInput& playerInput) override
        {
            InputManager* input = GET_SERVICE(InputManager);

            // Rotation (mouse)
            glm::dvec2 mouseDelta = input->GetMouseDelta();
            if (mouseDelta.x != 0.0 || mouseDelta.y != 0.0)
            {
                transform.m_Rotation.y -= glm::radians((float)mouseDelta.x * playerInput.m_RotationSpeed);
                transform.m_Rotation.x  = glm::clamp(transform.m_Rotation.x + glm::radians((float)mouseDelta.y * playerInput.m_RotationSpeed),
                                                      glm::radians(-playerInput.m_PitchLimit),
                                                      glm::radians( playerInput.m_PitchLimit));
            }

            // Translation
            glm::vec3 direction = glm::vec3(0.0f);
            if(input->IsKeyPressed(KEYCODE_W))  direction += transform.m_Forward;
            if(input->IsKeyPressed(KEYCODE_S))  direction -= transform.m_Forward;
            if(input->IsKeyPressed(KEYCODE_A))  direction += transform.m_Right;
            if(input->IsKeyPressed(KEYCODE_D))  direction -= transform.m_Right;
            if(input->IsKeyPressed(KEYCODE_SPACE))  direction += glm::vec3(0.0f, 1.0f, 0.0f);
            if(input->IsKeyPressed(KEYCODE_LEFT_CONTROL)) direction -= glm::vec3(0.0f, 1.0f, 0.0f);

            if (glm::length(direction) > 0.0f)
                direction = glm::normalize(direction);

            transform.m_Position     += direction * playerInput.m_MovementSpeed * deltaTime;
            transform.m_Dirty = true;
        }

        const char* GetName() override { return "InputSystem"; }
    };
}
