#pragma once
#include "Layer.h"

#include <ForgexScene.h>
#include <ForgexGraphics.h>
#include <ForgexDebugTools.h>

#include "../MovementSystem.h"

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
            int ent = m_ActiveScene->CreateEntity("FirstEntity");

            m_ActiveScene->AddSystem<MovementSystem>();
        }

		void OnUpdate(float deltaTime) override
		{
			m_ActiveScene->Update(deltaTime);
		}

		void OnRender() override
		{
			//Graphics::Resources::RenderView renderView{};
			//renderView.m_ViewMatrix = m_EditorCamera->GetViewMatrix();
			//renderView.m_ProjectionMatrix = m_EditorCamera->GetProjectionMatrix();

			//Graphics::SceneRenderer renderer;
			//renderer.Render(&renderView);
		}

		void OnEvent(Event* event) override {}
		void OnDetach() override {}
		void OnEnd() override {}

	private:
		Scene::Scene* m_ActiveScene = nullptr;
	};
}
