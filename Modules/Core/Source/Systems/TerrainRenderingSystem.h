#pragma once
#include <ForgexScene.h>
#include <ForgexAssets.h>
#include <ForgexGraphics.h>
#include <ForgexVoxel.h>
#include <glm/gtc/matrix_transform.hpp>

#include "../AssetTypes/ShaderAsset.h"

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
            auto chunkCollection = registry.view<Voxel::Chunk>();
            for(entt::entity entity : chunkCollection)
            {
                Voxel::Chunk& chunk = chunkCollection.get<Voxel::Chunk>(entity);

                renderInfos.emplace_back // Need to make the asset manager a singleton so we're able to request asset loading from wherever
                (
                    Assets::AssetManager::Get().LoadAsset<ShaderAsset>("Resources/Shaders/ColorShader.FShader")->GetShaderID(),
                    -1,
                    chunk.m_ModelMatrix,
                    chunk.vertexBufferID,
                    chunk.indexBufferID,
                    chunk.m_Indices.size()
                );
            }

            renderer.RenderMap(&renderView, &renderInfos);
        }
    };
}
