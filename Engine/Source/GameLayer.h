#pragma once
#include <ForgexCore.h>
#include <ForgexScene.h>
#include <ForgexGraphics.h>

namespace Forgex::Engine
{
    class GameLayer : public Core::Layer::Layer
    {
    public:
        GameLayer() : Core::Layer::Layer("Game Layer") {}

        void OnAttach() override {}

        void OnDetach() override {}

        void OnBegin() override
        {
            Scene::SceneManager* sceneManager = Core::ServiceLocator::Get().Fetch<Scene::SceneManager>();

            sceneManager->LoadScene(new Scene::Scene("Default Scene"));
            Scene::Scene* activeScene = sceneManager->GetActiveScene();

            // Temp for now to test if the skybox rendering is still working
            int skyboxEntity = activeScene->CreateEntity("Skybox");
            Graphics::Components::Skybox& skybox = activeScene->AddComponent<Graphics::Components::Skybox>(skyboxEntity);
            Graphics::Components::Renderable& renderable = activeScene->AddComponent<Graphics::Components::Renderable>(skyboxEntity);

            renderable.m_Vertices = skybox.m_SkyboxVertices.data();
            renderable.m_VertexBufferID = Graphics::Utils::BufferManager::GenerateBuffer(Graphics::Utils::BufferType::VertexBuffer, sizeof(float) * skybox.m_SkyboxVertices.size(), renderable.m_Vertices);

            renderable.m_ShaderAsset = Core::ServiceLocator::Get().Fetch<Assets::AssetManager>()->LoadAsset<Graphics::ShaderAsset>("Resources/Shaders/Skybox.FShader");
            renderable.m_TextureAsset = Core::ServiceLocator::Get().Fetch<Assets::AssetManager>()->LoadAsset<Graphics::TextureAsset>("Resources/Textures/Skybox.FTexture", Graphics::TextureType::Cubemap);
            // ==============================================================

            int cameraEntity = activeScene->CreateEntity("Main Camera");
            activeScene->AddComponent<Graphics::Components::Camera>(cameraEntity);
        }

        void OnEnd() override {}

        void OnUpdate(float deltaTime) override { Core::ServiceLocator::Get().Fetch<Scene::SceneManager>()->Update(deltaTime); }

        void OnEvent(Core::Layer::Event::Event* event) override {}

        void OnRender() override { Core::ServiceLocator::Get().Fetch<Scene::SceneManager>()->Render(); }
    };
}
