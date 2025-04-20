#pragma once
#include "Layer.h"
#include "../Event/EventList.h"

#include <ForgexScene.h>
#include <ForgexGraphics.h>

using namespace Forgex;

const std::vector<float> cubeVertices =
{
	-0.5f, -0.5f,  0.5f, // 0
	 0.5f, -0.5f,  0.5f, // 1
	 0.5f,  0.5f,  0.5f, // 2
	-0.5f,  0.5f,  0.5f  // 3
};

const std::vector<int> cubeIndices =
{
	0, 1, 2,
	0, 2, 3
};

const std::vector<float> cubeUVs =
{
	// uv
	0.0f, 0.0f, // 0
	1.0f, 0.0f, // 1
	1.0f, 1.0f, // 2
	0.0f, 1.0f  // 3
};

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

	void OnAttach() override
	{
	}

	void OnBegin() override 
	{
		m_ActiveScene = new Scene::Scene("Default Scene");
		m_SceneRenderProxy = new Graphics::SceneRenderProxy();
		m_EditorCameraObject = new Scene::Object("Camera Object");
		m_EditorCamera = m_EditorCameraObject->AddComponent<Scene::CameraComponent>();

		m_EditorCameraObject->GetTransform()->SetPosition(Math::Vec3(0, 0, 2));
		
		Scene::Object* meshObj = m_ActiveScene->CreateObject("Cube");
		Scene::MeshComponent* meshComponent = meshObj->AddComponent<Scene::MeshComponent>();
		meshComponent->SetMesh
		(
			cubeVertices,
			cubeIndices,
			cubeUVs,
			Graphics::Utils::ShaderLoader::LoadShader("Resources/Shaders/Texture.vertex", "Resources/Shaders/Texture.fragment"),
			Graphics::Utils::TextureLoader::LoadDefaultTexture(Graphics::Utils::Default, "Resources/Textures/edge2.png")
		);
	}

	void OnUpdate(float deltaTime) override
	{
		m_ActiveScene->Update(deltaTime);

		//m_EditorCameraObject->GetTransform()->SetRotationY(m_EditorCameraObject->GetTransform()->GetRotation().y + 0.2f * deltaTime);
		//m_EditorCameraObject->GetTransform()->SetPosition(m_EditorCameraObject->GetTransform()->GetPosition() + Math::Vec3(1.0f, 0.0f, 0.0f) * deltaTime);
		
		SyncRenderProxy();
	}

	void OnRender() override
	{
		Graphics::Resources::RenderView renderView{};
		renderView.m_ViewMatrix = m_EditorCamera->GetViewMatrix();
		renderView.m_ProjectionMatrix = m_EditorCamera->GetProjectionMatrix();
		
		Graphics::SceneRenderer renderer;
		renderer.Render(&renderView, m_SceneRenderProxy);
	}

	void OnEvent(Event& event) override
	{
	}

	void OnDetach() override
	{
	}

	void OnEnd() override
	{
	}

private:
	Scene::Scene* m_ActiveScene = nullptr;
	Graphics::SceneRenderProxy* m_SceneRenderProxy = nullptr;
	Scene::Object* m_EditorCameraObject = nullptr;
	Scene::CameraComponent* m_EditorCamera = nullptr;
	
	void SyncRenderProxy()
	{
		for (const Scene::Object* obj : *m_ActiveScene)
		{
			for(const Scene::Component* component : *obj)
			{
				if(const Scene::IRenderObject* renderComponent = dynamic_cast<const Scene::IRenderObject*>(component))
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