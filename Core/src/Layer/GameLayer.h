#pragma once
#include "Layer.h"
#include "../SceneGraph/Scene.h"
#include "../SceneGraph/Camera.h"
#include "../SceneGraph/Voxels/ChunkManager.h"
#include "../SceneGraph/PlayerController.h"

class GameLayer : public Layer
{
	using EventCallbackFn = std::function<void(Event&)>;

public:
	GameLayer() : Layer("Game") {};
	GameLayer(const EventCallbackFn& callback) : Layer("Game", callback) {};
	
	~GameLayer() 
	{
		delete m_ActiveScene;
	}

	void OnAttach() override
	{
		m_ActiveScene = new Scene("Default Scene");
		//Object* cameraObj = m_ActiveScene->CreateObject("Camera", glm::vec3(0.0f, 70.0f, 0.0f));
		//cameraObj->AddComponent<Camera>();
		//cameraObj->AddComponent<PlayerController>();
		
		//Object* chunkObj = m_ActiveScene->CreateObject("Chunk Manager");
		//chunkObj->AddComponent<ChunkManager>(cameraObj);
	}

	void OnBegin() override 
	{
		SceneChangeEvent e(m_ActiveScene);
		m_EventCallback(e);
	}

	void OnUpdate(float deltaTime) override 
	{
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