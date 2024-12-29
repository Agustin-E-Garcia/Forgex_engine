#pragma once
#include "Layer.h"
#include "../SceneGraph/Scene.h"
#include "../SceneGraph/Camera.h"
#include "../SceneGraph/Voxels/ChunkManager.h"
#include "../SceneGraph/PlayerController.h"
#include "../SceneGraph/Skybox.h"

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
		std::vector<const char*> skyboxTextures
		{
			"Resources/Textures/right.jpg",
			"Resources/Textures/left.jpg",
			"Resources/Textures/up.jpg",
			"Resources/Textures/down.jpg",
			"Resources/Textures/front.jpg",
			"Resources/Textures/back.jpg"
		};
		m_Skybox = new Skybox(skyboxTextures);

		m_ActiveScene = new Scene("Default Scene");
		Object* cameraObj = m_ActiveScene->CreateObject("Camera", glm::vec3(0.0f, 70.0f, 0.0f));
		cameraObj->AddComponent<Camera>();
		cameraObj->AddComponent<PlayerController>();
		
		//Object* chunkObj = m_ActiveScene->CreateObject("Chunk Manager");
		//chunkObj->AddComponent<ChunkManager>();
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
		renderer.PreSceneRender();
		renderer.DrawSkybox(m_Skybox->GetDrawInfo());
		m_ActiveScene->Render(renderer);
		renderer.PostSceneRender();
	}

	void OnEvent(Event& event) override
	{
	}

	inline Scene* GetActiveScene() { return m_ActiveScene; };

private:
	Scene* m_ActiveScene = nullptr;
	Skybox* m_Skybox = nullptr;
};