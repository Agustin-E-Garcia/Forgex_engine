#pragma once
#include "Layer.h"

#include <ForgexScene.h>
#include <ForgexGraphics.h>
#include <ForgexDebugTools.h>
#include <ForgexAssets.h>

#include "../AssetTypes/TextureAsset.h"
#include "../AssetTypes/ShaderAsset.h"

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

            int cameraEntity = m_ActiveScene->CreateEntity("MainCamera");
            m_ActiveScene->AddComponent<Scene::Camera>(cameraEntity);

            int boxEntity = m_ActiveScene->CreateEntity("Box");
            Scene::Render& renderComponent = m_ActiveScene->AddComponent<Scene::Render>(boxEntity);

            renderComponent.m_TextureID = m_AssetManager->LoadAsset<TextureAsset>("Resources/Textures/edge2.png")->GetTextureID();
            renderComponent.m_ShaderID = m_AssetManager->LoadAsset<ShaderAsset>("Resources/Shaders/Texture.FShader")->GetShaderID();
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
                renderView.m_ProjectionMatrix = glm::perspective(camera.m_FieldOfView, (camera.m_AspectRatio.x / camera.m_AspectRatio.y), camera.m_NearPlane, camera.m_FarPlane);
            }

            auto renderCollection = m_ActiveScene->GetRegistry().view<Scene::Transform, Scene::Render>();
            std::vector<Graphics::Resources::RenderInfo> renderInfos;
            for(entt::entity entity : renderCollection)
            {
                Scene::Render& render = renderCollection.get<Scene::Render>(entity);
                const Scene::Transform& transform = renderCollection.get<Scene::Transform>(entity);

                if(render.m_VertexBufferID == -1)
                    render.m_VertexBufferID = Graphics::Utils::BufferManager::GenerateBuffer
                        (
                            Graphics::Utils::BufferType::VertexBuffer, 
                            sizeof(float) * render.m_VertexSize, 
                            render.m_Vertices
                        );

                if(render.m_IndexBufferID == -1)
                    render.m_IndexBufferID = Graphics::Utils::BufferManager::GenerateBuffer
                        (
                            Graphics::Utils::BufferType::IndexBuffer,
                            render.m_IndexSize,
                            render.m_Indices
                        );

                renderInfos.emplace_back(render.m_ShaderID, render.m_TextureID, transform.m_ModelMatrix, render.m_VertexBufferID, render.m_IndexBufferID, render.m_IndexSize);
            }

            m_SceneRenderer.Render(&renderView, &renderInfos);
        }

        void OnEvent(Event* event) override {}
        void OnDetach() override {}
        void OnEnd() override {}

    private:
        Scene::Scene* m_ActiveScene = nullptr;
        Assets::AssetsManager* m_AssetManager = nullptr;
        Graphics::SceneRenderer m_SceneRenderer;
    };
}
