#include "Application.h"

#include "Log.h"
#include "DeltaTime.h"

#include "InputManager.h"

#include "Renderer.h"
#include "Layer/ImGUIOverlay.h"

#include "Camera.h"
#include "Voxels/ChunkManager.h"
#include "Scene.h"

Application* Application::s_Instance = nullptr;

Application::Application() 
{
	if (s_Instance == nullptr)
		s_Instance = this;
	else
		delete this;

	m_ShouldClose = false;
	InitializeSystems();
}

Application::~Application() 
{
	delete m_Renderer;
	delete m_Window;
}

void Application::InitializeSystems()
{
	Log::Init();
	DeltaTime::Init();
	m_Window = new Window(1720, 1080, "Voxel_Engine");
	m_Window->SetEventCallback(BIND_EVENT_FUNCTION(Application::HandleEvents));
	m_Renderer = new Renderer();

	PushOverlay(new ImGUIOverlay());
}

void Application::HandleEvents(Event& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNCTION(Application::OnWindowClose));

	for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
	{
		(*--it)->OnEvent(event);
		if (event.m_Handled)
			break;
	}
}

bool Application::OnWindowClose(WindowCloseEvent& e) 
{
	m_ShouldClose = true;
	return true;
}

void Application::PushLayer(Layer* layer) 
{
	m_LayerStack.PushLayer(layer);
}

void Application::PushOverlay(Layer* layer) 
{
	m_LayerStack.PushOverlay(layer);
}

void Application::Run()
{
	Scene scene;
	scene.CreateObject<Camera>(glm::vec3(0.0f, 70.0f, 0.0f));

	Camera* camera = scene.GetObjectOfType<Camera>();
	m_Renderer->SetActiveCamera(camera);
	
	ChunkManager* manager = scene.CreateObject<ChunkManager>(camera->GetTransform()->GetPosition());

	glm::vec3 speed = glm::vec3(0.0f);

	int cameraX = Profiler::AddProfile("Camera Pos X", 0);
	int cameraY = Profiler::AddProfile("Camera Pos Y", 0);
	int cameraZ = Profiler::AddProfile("Camera Pos Z", 0);

	do
	{
		float deltaTime = DeltaTime::Update();

		m_Renderer->ClearScreen();

		for (Layer* layer : m_LayerStack)
			layer->OnUpdate(deltaTime);

		{
			if (InputManager::IsKeyPressed(GLFW_KEY_A))				speed.x = 10.0;
			if (InputManager::IsKeyPressed(GLFW_KEY_D))				speed.x = -10.0;
			if (InputManager::IsKeyPressed(GLFW_KEY_W))				speed.z = 20.0;
			if (InputManager::IsKeyPressed(GLFW_KEY_S))				speed.z = -20.0;
			if (InputManager::IsKeyPressed(GLFW_KEY_LEFT_SHIFT))	speed.y = -20.0;
			if (InputManager::IsKeyPressed(GLFW_KEY_SPACE))			speed.y = 20.0;

			camera->GetTransform()->SetPosition (camera->GetTransform()->GetPosition() + camera->GetTransform()->GetForward() * speed.z * deltaTime);
			camera->GetTransform()->SetPosition (camera->GetTransform()->GetPosition() + camera->GetTransform()->GetUp() * speed.y * deltaTime);
			camera->GetTransform()->SetRotationY(camera->GetTransform()->GetRotation().y + speed.x * deltaTime);
			speed = glm::vec3(0);

			Profiler::UpdateProfile(cameraX, camera->GetTransform()->GetPosition().x);
			Profiler::UpdateProfile(cameraY, camera->GetTransform()->GetPosition().y);
			Profiler::UpdateProfile(cameraZ, camera->GetTransform()->GetPosition().z);
		}

		{
			manager->Update(camera->GetTransform()->GetPosition());
		
			auto drawInfos = manager->GetDrawInfo();
			for (int i = 0; i < drawInfos.size(); i++)
			{
				m_Renderer->DrawVoxel(drawInfos[i]);
			}
		}
		
		for (Layer* layer : m_LayerStack)
			layer->OnRender(*m_Renderer);

		m_Window->Update();

	} while (!m_ShouldClose);
}