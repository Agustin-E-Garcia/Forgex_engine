#pragma once
#include <ForgexCore.h>
#include <ForgexGraphics.h>
#include <ForgexScene.h>
#include <imgui.h>

namespace Forgex::Editor::Systems
{
    class GizmoSystem : public Core::Interfaces::ISystem
    {
        void Render(entt::registry &registry) override
        {
            glm::mat4 viewProj(1.0f);
            auto cameraView = registry.view<Graphics::Components::Camera, Core::Components::Transform>();
            for (const auto [entity, camera, transform] : cameraView.each())
            {
                if (!camera.m_IsActiveCamera) continue;
                glm::mat4 view = glm::lookAt(transform.m_Position, transform.m_Position + transform.m_Forward, glm::vec3(0.0f, 1.0f, 0.0f));
                glm::mat4 proj = glm::perspective(glm::radians(camera.m_FieldOfView), camera.m_AspectRatio.x / camera.m_AspectRatio.y, camera.m_NearPlane, camera.m_FarPlane);
                viewProj = proj * view;
                break;
            }

            ImGuiIO& io = ImGui::GetIO();
            ImDrawList* dl = ImGui::GetBackgroundDrawList(); // always behind all ImGui windows

            auto lightView = registry.view<Scene::Components::EntityInfo, Core::Components::Transform, Graphics::Components::PointLight>();
            for (const auto [entity, info, transform, light] : lightView.each())
            {
                glm::vec4 clip = viewProj * glm::vec4(transform.m_Position, 1.0f);
                if (clip.w <= 0.0f) continue;

                ImVec2 screen = WorldToScreen(transform.m_Position, viewProj, io.DisplaySize);

                dl->AddCircleFilled(screen, 8.0f, IM_COL32(255, 220, 80, 200));
                dl->AddCircle(screen, 8.0f, IM_COL32(255, 255, 255, 180), 12, 1.5f);
                dl->AddText({ screen.x + 12, screen.y - 7 }, IM_COL32(255, 255, 255, 200), info.m_EntityName);
            }
        }

        ImVec2 WorldToScreen(const glm::vec3& worldPos, const glm::mat4& viewProj, ImVec2 displaySize)
        {
            glm::vec4 clip = viewProj * glm::vec4(worldPos, 1.0f);
            glm::vec3 ndc  = glm::vec3(clip) / clip.w;

            float x = (ndc.x *  0.5f + 0.5f) * displaySize.x;
            float y = (ndc.y * -0.5f + 0.5f) * displaySize.y; // Y flipped

            return { x, y };
        }

        const char * GetName() override { return "GizmoSystem"; }
    };
}
