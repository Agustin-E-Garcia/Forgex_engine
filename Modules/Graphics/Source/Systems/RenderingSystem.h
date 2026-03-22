#pragma once
#include <ForgexCore.h>

#include "../Resources/RenderView.h"
#include "../Renderers/SceneRenderer.h"
#include "../Renderers/SkyboxRenderer.h"

#include "../Components/Camera.h"
#include "../Components/Renderable.h"
#include "../Components/Skybox.h"

namespace Forgex::Graphics::Systems
{
    class RenderingSystem : public Core::Interfaces::ISystem
    {
    public:
        void Render(entt::registry& registry) override 
        {
            Resources::RenderView renderView;
            auto view_camera = registry.view<Components::Camera, Core::Components::Transform>();
            for (entt::entity entity : view_camera)
            {
                const Components::Camera& camera = view_camera.get<Components::Camera>(entity);
                if(!camera.m_IsActiveCamera) continue;

                const Core::Components::Transform& transform = view_camera.get<Core::Components::Transform>(entity);
                renderView.m_ViewMatrix = glm::lookAt(transform.m_Position, transform.m_Position + transform.m_Forward, glm::vec3(0.0f, 1.0f, 0.0f));
                renderView.m_ProjectionMatrix = glm::perspective(glm::radians(camera.m_FieldOfView), (camera.m_AspectRatio.x / camera.m_AspectRatio.y), camera.m_NearPlane, camera.m_FarPlane);
            }

            Renderers::SkyboxRenderer renderer;
            auto view_renderable = registry.view<Components::Skybox, Components::Renderable>();
            for(entt::entity entity : view_renderable)
            {
                renderer.Render(renderView, view_renderable.get<Components::Renderable>(entity));
            }
        }

        const char* GetName() override { return "RenderingSystem"; }
    };
}
