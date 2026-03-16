#pragma once
#include "Layer.h"

#include <ForgexScene.h>
#include <ForgexGraphics.h>
#include <ForgexAssets.h>
#include <ForgexVoxel.h>

#include "../AssetTypes/ShaderAsset.h"
#include "../Systems/MovementSystem.h"
#include "glm/trigonometric.hpp"

namespace Forgex::Core
{
    class GameLayer : public Layer
    {
    using EventCallbackFn = std::function<void(Event&)>;

    public:
        GameLayer() : Layer("Game") {}
        GameLayer(const EventCallbackFn& callback) : Layer("Game", callback) {}

        ~GameLayer() override
        {
            delete m_ActiveScene;
        }

        void OnAttach() override {}

        void OnBegin() override
        {
            m_ActiveScene = new Scene::Scene("Default Scene");
            m_AssetManager = new Assets::AssetsManager();
            m_ActiveMap = new Voxel::VoxelMap();

            for (Voxel::Chunk& chunk : *m_ActiveMap)
            {
                chunk.vertexBufferID = Graphics::Utils::BufferManager::GenerateBuffer
                (
                    Graphics::Utils::BufferType::VertexBuffer,
                    chunk.GetVertexCount() * 6 * sizeof(float),
                    chunk.GetVertices()
                );
            }

            int cameraEntity = m_ActiveScene->CreateEntity("MainCamera");
            m_ActiveScene->AddComponent<Scene::Camera>(cameraEntity);
            m_ActiveScene->AddComponent<Scene::PlayerControlled>(cameraEntity);

            m_ActiveScene->AddSystem<MovementSystem>();
        }

        void OnUpdate(float deltaTime) override
        {
            m_ActiveScene->Update(deltaTime);
        }

        void OnRender() override
        {
            auto cameraCollection = m_ActiveScene->GetRegistry().view<Scene::Camera, Scene::Transform>();
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
            for(Voxel::Chunk& chunk : *m_ActiveMap)
            {
                renderInfos.emplace_back
                (
                    m_AssetManager->LoadAsset<ShaderAsset>("Resources/Shaders/ColorShader.FShader")->GetShaderID(),
                    -1,
                    chunk.GetModelMatrix(),
                    chunk.vertexBufferID,
                    -1,
                    chunk.GetVertexCount()
                );
            }

            renderer.RenderMap(&renderView, &renderInfos);
        }

        void OnEvent(Event* event) override {}

        void OnDetach() override {}
        void OnEnd() override {}

    private:
        Scene::Scene* m_ActiveScene = nullptr;
        Voxel::VoxelMap* m_ActiveMap = nullptr;
        Assets::AssetsManager* m_AssetManager = nullptr;
        Graphics::SceneRenderer m_SceneRenderer;
    };
}
