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

        void OnAttach() override { m_ActiveScene = new Scene::Scene("Default Scene"); }

        void OnDetach() override {}

        void OnBegin() override 
        {
            int cameraEntity = m_ActiveScene->CreateEntity("Main Camera");
            m_ActiveScene->AddComponent<Graphics::Camera>(cameraEntity);
        }

        void OnEnd() override {}

        void OnUpdate(float deltaTime) override { m_ActiveScene->Update(deltaTime); }

        void OnEvent(Core::Layer::Event::Event* event) override {}

        void OnRender() override { m_ActiveScene->Render(); }

    private:
        Scene::Scene* m_ActiveScene = nullptr;
    };
}
