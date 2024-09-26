#include "Application.h"

#include "Log.h"
#include "DeltaTime.h"

#include "InputManager.h"

#include "Renderer.h"
#include "Layer/ImGUIOverlay.h"
#include "Layer/GameLayer.h"

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

	m_GameLayer = new GameLayer(BIND_EVENT_FUNCTION(Application::HandleEvents));
	PushLayer(m_GameLayer);
	PushOverlay(new ImGUIOverlay(m_GameLayer->GetActiveScene()));
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
	Camera* camera = m_GameLayer->GetActiveScene()->GetObjectOfType<Camera>();
	if(camera) m_Renderer->SetActiveCamera(camera);
	else 
	{
		LOG_CORE_CRITICAL("Scene '{0}' has no camera to render from", m_GameLayer->GetActiveScene()->GetName());
	}

	do
	{
		float deltaTime = DeltaTime::Update();

		m_Renderer->ClearScreen();

		for (Layer* layer : m_LayerStack)
			layer->OnUpdate(deltaTime);
		
		for (Layer* layer : m_LayerStack)
			layer->OnRender(*m_Renderer);

		m_Window->Update();

	} while (!m_ShouldClose);
}