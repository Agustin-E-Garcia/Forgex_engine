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
                float yawDelta   = (float)mouseDelta.x * playerInput.m_RotationSpeed;
                float pitchDelta = (float)mouseDelta.y * playerInput.m_RotationSpeed;

                playerInput.m_Yaw  += yawDelta;
                playerInput.m_Pitch = glm::clamp(playerInput.m_Pitch + pitchDelta,
                                                  -playerInput.m_PitchLimit,
                                                   playerInput.m_PitchLimit);

                glm::quat yawRot   = glm::angleAxis(glm::radians(-playerInput.m_Yaw),   glm::vec3(0.0f, 1.0f, 0.0f));
                glm::quat pitchRot = glm::angleAxis(glm::radians(-playerInput.m_Pitch), glm::vec3(1.0f, 0.0f, 0.0f));

                transform.m_RotationQuat   = glm::normalize(yawRot * pitchRot);
                transform.m_Forward        = glm::normalize(transform.m_RotationQuat * glm::vec3(0.0f, 0.0f, -1.0f));
                transform.m_Right          = glm::normalize(transform.m_RotationQuat * glm::vec3(1.0f, 0.0f, 0.0f));
                transform.m_RotationMatrix = glm::mat4_cast(transform.m_RotationQuat);
            }

            // Translation
            glm::vec3 direction = glm::vec3(0.0f);
            if(input->IsKeyPressed(KEYCODE_W))  direction += transform.m_Forward;
            if(input->IsKeyPressed(KEYCODE_S))  direction -= transform.m_Forward;
            if(input->IsKeyPressed(KEYCODE_A))  direction -= transform.m_Right;
            if(input->IsKeyPressed(KEYCODE_D))  direction += transform.m_Right;
            if(input->IsKeyPressed(KEYCODE_SPACE))  direction += glm::vec3(0.0f, 1.0f, 0.0f);
            if(input->IsKeyPressed(KEYCODE_LEFT_CONTROL)) direction -= glm::vec3(0.0f, 1.0f, 0.0f);

            if (glm::length(direction) > 0.0f)
                direction = glm::normalize(direction);

            transform.m_Position     += direction * playerInput.m_MovementSpeed * deltaTime;
            transform.m_LocationMatrix = glm::translate(glm::mat4(1.0f), transform.m_Position);
        }

        const char* GetName() override { return "InputSystem"; }
    };
}
