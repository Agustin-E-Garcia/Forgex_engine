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
            auto cameraCollection = registry.view<Scene::Camera, Scene::Transform>();
            Graphics::Resources::RenderView renderView{};

            for (entt::entity entity : cameraCollection)
            {
                const Scene::Camera& camera = cameraCollection.get<Scene::Camera>(entity);
                if(!camera.m_IsActiveCamera) continue;

                const Scene::Transform transform = cameraCollection.get<Scene::Transform>(entity);
                renderView.m_ViewMatrix = glm::lookAt(transform.m_Position, transform.m_Position + transform.m_Forward, glm::vec3(0.0f, 1.0f, 0.0f));
                renderView.m_ProjectionMatrix = glm::perspective(glm::radians(camera.m_FieldOfView), (camera.m_AspectRatio.x / camera.m_AspectRatio.y), camera.m_NearPlane, camera.m_FarPlane);
            }

            Graphics::SceneRenderer renderer;
            std::vector<Graphics::Resources::RenderInfo> renderInfos;
            auto chunkCollection = registry.view<Voxel::Chunk, Graphics::Renderable>();
            for(entt::entity entity : chunkCollection)
            {
                Graphics::Renderable& chunk = chunkCollection.get<Graphics::Renderable>(entity);

                renderInfos.emplace_back
                (
                    chunk.m_ShaderAsset->GetShaderID(),
                    -1,
                    chunk.m_ModelMatrix,
                    chunk.m_VertexBufferID,
                    chunk.m_IndexBufferID,
                    chunk.m_IndexSize
                );
            }

            renderer.RenderMap(&renderView, &renderInfos);
        }
    };
}
