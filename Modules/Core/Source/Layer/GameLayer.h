#pragma once
#include "Layer.h"

#include <ForgexScene.h>
#include <ForgexGraphics.h>
#include <ForgexDebugTools.h>

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
			delete m_EditorCameraObject;
		}

		void OnAttach() override {}

		void OnBegin() override
		{
			m_ActiveScene = new Scene::Scene("Default Scene");
			m_EditorCameraObject = m_ActiveScene->CreateObject("Editor Camera"); //new Scene::Object("Camera Object");
			m_EditorCamera = m_EditorCameraObject->AddComponent<Scene::CameraComponent>();

			m_EditorCameraObject->GetTransform()->SetPosition(glm::vec3(0, 0, 2));

			m_ActiveScene->CreateObject("Game Camera");
			m_ActiveScene->CreateObject("Terrain");
		}

		void OnUpdate(float deltaTime) override
		{
			m_ActiveScene->Update(deltaTime);
		}

		void OnRender() override
		{
			Graphics::Resources::RenderView renderView{};
			renderView.m_ViewMatrix = m_EditorCamera->GetViewMatrix();
			renderView.m_ProjectionMatrix = m_EditorCamera->GetProjectionMatrix();

			Graphics::SceneRenderer renderer;
			renderer.Render(&renderView);
		}

		void OnEvent(Event* event) override {}
		void OnDetach() override {}
		void OnEnd() override {}

	private:
		Scene::Scene* m_ActiveScene = nullptr;
		Scene::Object* m_EditorCameraObject = nullptr;
		Scene::CameraComponent* m_EditorCamera = nullptr;

	};
}
