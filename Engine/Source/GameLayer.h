#pragma once
#include "Input/InputManager.h"
#include "Input/PlayerInput.h"
#include "glm/fwd.hpp"

#include <ForgexCore.h>
#include <ForgexScene.h>
#include <ForgexGraphics.h>

namespace Forgex::Engine
{
    class GameLayer : public Core::Interfaces::ILayer
    {
    public:
        GameLayer() : Core::Interfaces::ILayer("Game Layer") {}

        void OnAttach() override {}

        void OnDetach() override {}

        void OnBegin() override
        {
            Scene::SceneManager* sceneManager = Core::ServiceLocator::Get().Fetch<Scene::SceneManager>();

            sceneManager->LoadScene(new Scene::Scene("Default Scene"));
            Scene::Scene* activeScene = sceneManager->GetActiveScene();

            int cameraEntity = activeScene->CreateEntity("Main Camera");
            activeScene->AddComponent<Graphics::Components::Camera>(cameraEntity);
            activeScene->AddComponent<Core::Components::Transform>(cameraEntity);
            activeScene->AddComponent<Input::PlayerInput>(cameraEntity);

            int meshEntity = activeScene->CreateEntity("Mesh Entity");
            Graphics::Components::Renderable& renderable = activeScene->AddComponent<Graphics::Components::Renderable>(meshEntity);
            Core::Components::Transform& transform = activeScene->AddComponent<Core::Components::Transform>(meshEntity);
            renderable.m_MeshAsset = GET_SERVICE(Assets::AssetManager)->LoadAsset<Graphics::MeshAsset>("Resources/Meshes/Teapot.obj");
            renderable.m_MaterialAsset = GET_SERVICE(Assets::AssetManager)->LoadAsset<Graphics::MaterialAsset>("Resources/Materials/Lit.FMaterial");
            renderable.m_ModelMatrix = transform.m_ModelMatrix;

            int lightEntity = activeScene->CreateEntity("Light Entity");
            activeScene->AddComponent<Graphics::Components::PointLight>(lightEntity);
            Core::Components::Transform& lightTransform = activeScene->AddComponent<Core::Components::Transform>(lightEntity);

            lightTransform.m_Position = glm::vec3(0.0f, 20.0f, 0.0f);
            lightTransform.m_Dirty = true;

            sceneManager->Setup();
        }

        void OnEnd() override {}

        void OnUpdate(float deltaTime) override
        {
            Core::ServiceLocator::Get().Fetch<Scene::SceneManager>()->Update(deltaTime);
            GET_SERVICE(Input::InputManager)->ResetMouseDelta();
        }

        void OnEvent(Core::Layer::Event::Event* event) override
        {
            Core::Layer::Event::EventDispatcher dispatcher(*event);
            dispatcher.Dispatch<Core::Layer::Event::KeyPressedEvent>(BIND_EVENT_FUNCTION(GameLayer::HandleKeyPressedEvent));
            dispatcher.Dispatch<Core::Layer::Event::KeyReleasedEvent>(BIND_EVENT_FUNCTION(GameLayer::HandleKeyReleasedEvent));
            dispatcher.Dispatch<Core::Layer::Event::MouseClickEvent>(BIND_EVENT_FUNCTION(GameLayer::HandleMouseClickEvent));
            dispatcher.Dispatch<Core::Layer::Event::MousePositionEvent>(BIND_EVENT_FUNCTION(GameLayer::HandleMousePositionEvent));
        }

        void OnRender() override { Core::ServiceLocator::Get().Fetch<Scene::SceneManager>()->Render(); }

    private:
        bool HandleKeyPressedEvent(Core::Layer::Event::KeyPressedEvent& event)
        {
            GET_SERVICE(Input::InputManager)->RegisterKeyState(event.GetKeyCode(), event.IsPressed());
            return false;
        }

        bool HandleKeyReleasedEvent(Core::Layer::Event::KeyReleasedEvent& event)
        {
            GET_SERVICE(Input::InputManager)->RegisterKeyState(event.GetKeyCode(), false);
            return false;
        }

        bool HandleMouseClickEvent(Core::Layer::Event::MouseClickEvent& event)
        {
            GET_SERVICE(Input::InputManager)->RegisterKeyState(event.GetButton(), event.IsPressed());
            return false;
        }

        bool HandleMousePositionEvent(Core::Layer::Event::MousePositionEvent& event)
        {
            GET_SERVICE(Input::InputManager)->UpdateMouseDelta(glm::dvec2(event.GetPositionX(), event.GetPositionY()));
            return false;
        }
    };
}
