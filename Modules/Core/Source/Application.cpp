#include "Application.h"
#include "Layer/GameLayer.h"
#include "Layer/UILayer.h"

#include <ForgexDebugTools.h>

#include <chrono>

struct DeltaTimeHandler
{
	std::chrono::steady_clock::time_point lastFrame = std::chrono::high_resolution_clock::now();
	
	float Update()
	{
		const auto currentFrame = std::chrono::high_resolution_clock::now();
		const std::chrono::duration<float> delta = currentFrame - lastFrame;
		lastFrame = currentFrame;
		return delta.count();
	}
};

Application::Application() : m_ShouldClose(false)
{
	InitializeSystems();
}

Application::~Application()
{
}

void Application::InitializeSystems()
{
	Debug::Log::Init();

	m_Window = new Graphics::Window(800, 600, "Forgex Engine");
	
	GameLayer* gameLayer = new GameLayer();
	m_LayerStack.PushLayer(gameLayer);

	UILayer* uiLayer = new UILayer();
	m_LayerStack.PushOverlay(uiLayer);
}

void Application::Run()
{
	DeltaTimeHandler deltaTime;
	
	for (Layer* layer : m_LayerStack)
		layer->OnBegin();
	
	do
	{
		for (Layer* layer : m_LayerStack)
			layer->OnUpdate(deltaTime.Update());

		for (Layer* layer : m_LayerStack)
			layer->OnRender();

		m_Window->Update();
		
	} while (!m_Window->ShouldClose());

	for (Layer* layer : m_LayerStack)
		layer->OnEnd();
}