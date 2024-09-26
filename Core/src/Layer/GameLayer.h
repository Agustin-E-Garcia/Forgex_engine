#pragma once
#include "Layer.h"
#include "../Scene.h"
#include "../Camera.h"
#include "../Voxels/ChunkManager.h"

class GameLayer : public Layer
{
	using EventCallbackFn = std::function<void(Event&)>;

public:
	GameLayer() : Layer("Game") {};
	GameLayer(const EventCallbackFn& callback) : Layer("Game", callback) {};
	~GameLayer() {}

	void OnAttach() override
	{
		m_ActiveScene = new Scene("Default Scene");
		Camera* camera = m_ActiveScene->CreateObject<Camera>(glm::vec3(0.0f, 70.0f, 0.0f));
		m_ActiveScene->CreateObject<ChunkManager>(camera);
	}

	void OnDetach() override
	{
		delete m_ActiveScene;
	}

	void OnUpdate(float deltaTime) override 
	{
		SceneChangeEvent e(m_ActiveScene);
		m_EventCallback(e);

		/* TEMP */
		glm::vec3 speed(0.0f);
		Camera* camera = m_ActiveScene->GetObjectOfType<Camera>();
		
		if (camera) 
		{
			if (InputManager::IsKeyPressed(GLFW_KEY_A))				speed.x =  10.0;
			if (InputManager::IsKeyPressed(GLFW_KEY_D))				speed.x = -10.0;
			if (InputManager::IsKeyPressed(GLFW_KEY_W))				speed.z =  20.0;
			if (InputManager::IsKeyPressed(GLFW_KEY_S))				speed.z = -20.0;
			if (InputManager::IsKeyPressed(GLFW_KEY_LEFT_SHIFT))	speed.y = -20.0;
			if (InputManager::IsKeyPressed(GLFW_KEY_SPACE))			speed.y =  20.0;
			
			camera->GetTransformUnsafe()->SetPosition(camera->GetTransform()->GetPosition() + camera->GetTransform()->GetForward() * speed.z * deltaTime);
			camera->GetTransformUnsafe()->SetPosition(camera->GetTransform()->GetPosition() + camera->GetTransform()->GetUp() * speed.y * deltaTime);
			camera->GetTransformUnsafe()->SetRotationY(camera->GetTransformUnsafe()->GetRotation().y + speed.x * deltaTime);
		}
		m_ActiveScene->Update(deltaTime);
	}

	void OnRender(const Renderer& renderer) 
	{
		m_ActiveScene->Render(renderer);
	}

	void OnEvent(Event& event) override
	{
	}

	inline Scene* GetActiveScene() { return m_ActiveScene; };

private:
	Scene* m_ActiveScene = nullptr;
};