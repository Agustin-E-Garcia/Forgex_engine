#pragma once
#include <ForgexScene.h>
#include <ForgexGraphics.h>
#include <ForgexVoxel.h>
#include <glm/gtc/matrix_transform.hpp>

namespace Forgex::Core
{
    class TerrainRenderSystem : public Scene::ISystem
    {
    public:
        SYSTEM_NAME(TerrainRenderSystem);
        SYSTEM_TYPE(RenderSystem)

        void Run(entt::registry& registry, float deltaTime) override
        {
            auto cameraCollection = registry.view<Graphics::Camera, Scene::Transform>();
            Graphics::Resources::RenderView renderView{};

            for (entt::entity entity : cameraCollection)
            {
                const Graphics::Camera& camera = cameraCollection.get<Graphics::Camera>(entity);
                if(!camera.m_IsActiveCamera) continue;

                const Scene::Transform transform = cameraCollection.get<Scene::Transform>(entity);
                renderView.m_ViewMatrix = glm::lookAt(transform.m_Position, transform.m_Position + transform.m_Forward, glm::vec3(0.0f, 1.0f, 0.0f));
                renderView.m_ProjectionMatrix = glm::perspective(glm::radians(camera.m_FieldOfView), (camera.m_AspectRatio.x / camera.m_AspectRatio.y), camera.m_NearPlane, camera.m_FarPlane);
            }

            Graphics::SceneRenderer renderer;
            std::vector<Graphics::Renderable> renderInfos;
            auto chunkCollection = registry.view<Voxel::Chunk, Graphics::Renderable>();
            for(entt::entity entity : chunkCollection)
            {
                renderInfos.push_back(chunkCollection.get<Graphics::Renderable>(entity));
            }

            renderer.RenderMap(&renderView, &renderInfos);
        }
    };
}
