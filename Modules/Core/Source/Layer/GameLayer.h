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
			delete m_SceneRenderProxy;
			delete m_EditorCameraObject;
		}

		void OnAttach() override {}

		void OnBegin() override
		{
			m_ActiveScene = new Scene::Scene("Default Scene");
			m_SceneRenderProxy = new Graphics::SceneRenderProxy();
			m_EditorCameraObject = new Scene::Object("Camera Object");
			m_EditorCamera = m_EditorCameraObject->AddComponent<Scene::CameraComponent>();

			m_EditorCameraObject->GetTransform()->SetPosition(Math::Vec3(0, 0, 2));
		}

		void OnUpdate(float deltaTime) override
		{
			m_ActiveScene->Update(deltaTime);
			SyncRenderProxy();
		}

		void OnRender() override
		{
			Graphics::Resources::RenderView renderView{};
			renderView.m_ViewMatrix = m_EditorCamera->GetViewMatrix();
			renderView.m_ProjectionMatrix = m_EditorCamera->GetProjectionMatrix();

			Graphics::SceneRenderer renderer;
			renderer.Render(nullptr, &renderView, m_SceneRenderProxy);
		}

		void OnEvent(Event* event) override {}
		void OnDetach() override {}
		void OnEnd() override {}

	private:
		Scene::Scene* m_ActiveScene = nullptr;
		Graphics::SceneRenderProxy* m_SceneRenderProxy = nullptr;
		Scene::Object* m_EditorCameraObject = nullptr;
		Scene::CameraComponent* m_EditorCamera = nullptr;

		void SyncRenderProxy()
		{
			for (const Scene::Object* obj : *m_ActiveScene)
			{
				for (const Scene::Component* component : *obj)
				{
					if (const Scene::IRenderObject* renderComponent = dynamic_cast<const Scene::IRenderObject*>(component))
					{
						m_SceneRenderProxy->SyncRenderObject
						(
							obj->GetUID(),
							renderComponent->GetVertices(),
							renderComponent->GetIndices(),
							renderComponent->GetUVs(),
							renderComponent->GetShaderID(),
							renderComponent->GetTextureID(),
							obj->GetTransform()->GetModelMatrix()
						);
					}
				}
			}

			m_SceneRenderProxy->Bake();
		}
	};
}
