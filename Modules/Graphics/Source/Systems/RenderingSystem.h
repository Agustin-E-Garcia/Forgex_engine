#pragma once
#include <ForgexCore.h>

#include "../Resources/RenderFrameData.h"
#include "../Renderers/SceneRenderer.h"
#include "../Renderers/SkyboxRenderer.h"

#include <ForgexAssets.h>

#include "../Components/Camera.h"
#include "../Components/Renderable.h"
#include "../Components/Skybox.h"

namespace Forgex::Graphics::Systems
{
    class RenderingSystem : public Core::Interfaces::ISystem
    {
    public:
        void Setup(entt::registry& registry) override
        {
            entt::entity skyboxEntity = registry.create();
            Components::Skybox& skybox = registry.emplace<Components::Skybox>(skyboxEntity);
            Components::Renderable& renderable = registry.emplace<Components::Renderable>(skyboxEntity);

            renderable.m_MeshAsset = GET_SERVICE(Assets::AssetManager)->CreateRuntimeAsset<MeshAsset>("Skybox_Mesh", skybox.m_SkyboxVertices.data(), skybox.m_SkyboxVertices.size());
            renderable.m_MaterialAsset = GET_SERVICE(Assets::AssetManager)->LoadAsset<MaterialAsset>("Resources/Materials/Skybox.FMaterial");
        }

        void Render(entt::registry& registry) override
        {
            Resources::RenderFrameData renderFrameData;
            auto view_camera = registry.view<Components::Camera, Core::Components::Transform>();
            for (entt::entity entity : view_camera)
            {
                const Components::Camera& camera = view_camera.get<Components::Camera>(entity);
                if(!camera.m_IsActiveCamera) continue;

                const Core::Components::Transform& transform = view_camera.get<Core::Components::Transform>(entity);
                renderFrameData.m_ViewMatrix = glm::lookAt(transform.m_Position, transform.m_Position + transform.m_Forward, glm::vec3(0.0f, 1.0f, 0.0f));
                renderFrameData.m_ProjectionMatrix = glm::perspective(glm::radians(camera.m_FieldOfView), (camera.m_AspectRatio.x / camera.m_AspectRatio.y), camera.m_NearPlane, camera.m_FarPlane);
            }

            auto view_light = registry.view<Components::PointLight, Core::Components::Transform>();
            for (entt::entity entity : view_light)
            {
                const Core::Components::Transform& transform = view_light.get<Core::Components::Transform>(entity);
                const Components::PointLight& light = view_light.get<Components::PointLight>(entity);

                renderFrameData.m_Lights.emplace_back(light, glm::vec3(glm::vec4(transform.m_Position, 1.0) * transform.m_ModelMatrix));
            }

            Renderers::SkyboxRenderer skybox_renderer;
            auto view_skybox = registry.view<Components::Skybox, Components::Renderable>();
            for(entt::entity entity : view_skybox)
            {
                skybox_renderer.Render(renderFrameData, view_skybox.get<Components::Renderable>(entity));
            }

            Renderers::SceneRenderer scene_renderer;
            auto view_renderable = registry.view<Components::Renderable>();
            std::vector<Components::Renderable> renderables;
            for(entt::entity entity : view_renderable)
            {
                Components::Renderable& renderable = view_renderable.get<Components::Renderable>(entity);
                if(IsValid(renderable)) renderables.push_back(renderable);
            }
            scene_renderer.Render(renderFrameData, renderables);
        }

        bool IsValid(const Components::Renderable& renderable) 
        {
            return  renderable.m_MeshAsset.IsValid() && renderable.m_MeshAsset->GetIndexBuffer() != -1 &&
                    renderable.m_MeshAsset->GetVertexBuffer() != -1;
        }

        const char* GetName() override { return "RenderingSystem"; }
    };
}
