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
                renderFrameData.m_ProjectionMatrix = glm::perspective
                (
                    glm::radians(camera.m_FieldOfView),
                    (camera.m_AspectRatio.x / camera.m_AspectRatio.y),
                    camera.m_NearPlane,
                    camera.m_FarPlane
                );

                renderFrameData.m_CameraPosition = glm::vec4(transform.m_Position, 1.0f);
            }

            auto view_directionalLight = registry.view<Components::DirectionalLight, Core::Components::Transform>();
            int index = 0;
            for (const auto&& [entity, light, transform] : view_directionalLight.each())
            {
                if(index >= 5) break;

                renderFrameData.m_DirectionalLights[index] = Resources::DirectionalLightData(light, transform.m_Forward);
                renderFrameData.m_DirectionalLightsCount += 1;
                index++;
            }

            auto view_pointLight = registry.view<Components::PointLight, Core::Components::Transform>();
            index = 0;
            for (const auto&& [entity, light, transform] : view_pointLight.each())
            {
                if(index >= 5) break;

                renderFrameData.m_PointLights[index] = Resources::PointLightData(light, glm::vec3(transform.m_Position));
                renderFrameData.m_PointLightsCount += 1;
                index++;
            }

            auto view_spotLight = registry.view<Components::SpotLight, Core::Components::Transform>();
            index = 0;
            for (auto&& [entity, light, transform] : view_spotLight.each())
            {
                if(index >= 5) break;

                renderFrameData.m_SpotLights[index] = Resources::SpotLightData
                    (
                        light,
                        transform.m_Position,
                        transform.m_Forward
                    );
                renderFrameData.m_SpotLightsCount += 1;
                index++;
            }

            Renderers::SkyboxRenderer skybox_renderer;
            auto view_skybox = registry.view<Components::Skybox, Components::Renderable>();
            for(entt::entity entity : view_skybox)
            {
                skybox_renderer.Render(renderFrameData, view_skybox.get<Components::Renderable>(entity));
            }

            Renderers::SceneRenderer scene_renderer;
            auto view_renderable = registry.view<Components::Renderable, Core::Components::Transform>();
            std::vector<Components::Renderable> renderables;
            for(auto&& [entity, renderable, transform] : view_renderable.each())
            {
                renderable.m_ModelMatrix = transform.m_ModelMatrix;
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
