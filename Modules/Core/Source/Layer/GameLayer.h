#pragma once
#include "Layer.h"

#include <ForgexScene.h>
#include <ForgexGraphics.h>
#include <ForgexVoxel.h>

#include "../Systems/MovementSystem.h"
#include "../Systems/VoxelTerrainSetupSystem.h"
#include "../Systems/ChunkMeshingSystem.h"
#include "../Systems/TerrainRenderingSystem.h"

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

            int cameraEntity = m_ActiveScene->CreateEntity("MainCamera");
            m_ActiveScene->AddComponent<Scene::Camera>(cameraEntity);
            m_ActiveScene->AddComponent<Scene::PlayerControlled>(cameraEntity);

            m_ActiveScene->RunSystem<VoxelTerrainSetupSystem>();

            m_ActiveScene->AddSystem<MovementSystem>();
            m_ActiveScene->AddSystem<ChunkMeshingSystem>();
            m_ActiveScene->AddSystem<TerrainRenderSystem>();
        }

        void OnUpdate(float deltaTime) override
        {
            m_ActiveScene->Update(deltaTime);
        }

        void OnRender() override
        {
            m_ActiveScene->Render();
        }

        void OnEvent(Event* event) override {}

        void OnDetach() override {}
        void OnEnd() override {}

    private:
        Scene::Scene* m_ActiveScene = nullptr;
        Graphics::SceneRenderer m_SceneRenderer;
    };
}
