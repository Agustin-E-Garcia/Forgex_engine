#include "pch.h"
#include "Application.h"

#include "Log.h"

#include "InputManager.h"

#include "Renderer.h"
#include "Layer/GameLayer.h"
#include "Layer/ImGUIOverlay.h"

#include "Profiler/Profiler.h"

Application* Application::s_Instance = nullptr;

Application::Application() : m_ShouldClose(false), m_Window(nullptr), m_Renderer(nullptr)
{
	if (s_Instance != nullptr) return;

	s_Instance = this;
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
	m_Window = new Window(1720, 1080, "Voxel_Engine");
	m_Window->SetEventCallback(BIND_EVENT_FUNCTION(Application::HandleEvents));
	m_Renderer = new Renderer();

	PushLayer(new GameLayer(BIND_EVENT_FUNCTION(Application::HandleEvents)));
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

Scene* Application::GetActiveScene()
{
	return m_LayerStack.GetLayerOfType<GameLayer>()->GetActiveScene();
}

void Application::SetActiveCamera(Camera* camera) 
{
	if (camera) s_Instance->m_Renderer->SetActiveCamera(camera);
}

static int32_t UpdateKey = -1;
static int32_t RenderKey = -1;


void Application::Run()
{
	for (Layer* layer : m_LayerStack)
		layer->OnBegin();

	Camera* camera = GetActiveScene()->GetComponentOfType<Camera>();
	if(camera) m_Renderer->SetActiveCamera(camera);

	do
	{
		m_DeltaTime.Update();

		m_Renderer->ClearScreen();

		{
			FunctionTimer timer("Update Loop", &UpdateKey);
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(m_DeltaTime.GetDeltaTime());
		}
		
		{
			FunctionTimer timer("Render Loop", &RenderKey);
			for (Layer* layer : m_LayerStack)
				layer->OnRender(*m_Renderer);
		}

		m_Window->Update();

	} while (!m_ShouldClose);

	for (Layer* layer : m_LayerStack)
		layer->OnEnd();
}