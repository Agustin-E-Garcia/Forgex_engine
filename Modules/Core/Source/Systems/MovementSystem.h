#pragma once
#include "glm/ext/matrix_transform.hpp"
#include <ForgexScene.h>
#include <ForgexGraphics.h>
#include <GLFW/glfw3.h>
#include <ForgexDebugTools.h>

namespace Forgex::Core
{
    class MovementSystem : public Scene::PerEntitySystem<Scene::Transform, Scene::PlayerControlled>
    {
    public:
        SYSTEM_NAME(MovementSystem);
        SYSTEM_TYPE(UpdateSystem);

        void OnUpdate(float deltaTime, entt::entity entity, Scene::Transform& transform, Scene::PlayerControlled& control) override
        {
            // Query inputs
            GLFWwindow* window = glfwGetCurrentContext();

            bool forward = glfwGetKey(window, GLFW_KEY_UP);
            bool back = glfwGetKey(window, GLFW_KEY_DOWN);
            bool left = glfwGetKey(window, GLFW_KEY_LEFT);
            bool right = glfwGetKey(window, GLFW_KEY_RIGHT);
            bool up = glfwGetKey(window, GLFW_KEY_SPACE);
            bool down = glfwGetKey(window, GLFW_KEY_LEFT_CONTROL);
            bool rotateLeft = glfwGetKey(window, GLFW_KEY_E);
            bool rotateRight = glfwGetKey(window, GLFW_KEY_Q);

            // Rotation
            if (rotateLeft || rotateRight)
            {
                float yawDelta = (rotateRight ? 1.0f : -1.0f) * control.rotateSpeed * deltaTime;
                glm::quat yawRot = glm::angleAxis(glm::radians(yawDelta), glm::vec3(0.0f, 1.0f, 0.0f));
                transform.m_RotationQuat = glm::normalize(yawRot * transform.m_RotationQuat);
                transform.m_Forward = glm::normalize(transform.m_RotationQuat * glm::vec3(0.0f, 0.0f, -1.0f));
                transform.m_Right = glm::normalize(transform.m_RotationQuat * glm::vec3(1.0f, 0.0f, 0.0f));
                transform.m_RotationMatrix = glm::mat4_cast(transform.m_RotationQuat);
            }

            // Translation
            glm::vec3 direction = glm::vec3(0.0f);
            if(forward) direction += transform.m_Forward;
            if(back) direction += transform.m_Forward * -1.0f;
            if(left) direction += transform.m_Right * -1.0f;
            if(right) direction += transform.m_Right;
            if(up) direction += glm::vec3(0.0f, 1.0f, 0.0f);
            if(down) direction += glm::vec3(0.0f, -1.0f, 0.0f);

            transform.m_Position += direction * control.moveSpeed * deltaTime;
            transform.m_LocationMatrix = glm::translate(glm::mat4(1.0f), transform.m_Position);
        }
    };
}
