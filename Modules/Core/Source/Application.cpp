#include "Application.h"
#include "Layer/GameLayer.h"
#include "Layer/UILayer.h"

#include <ForgexDebugTools.h>

#include <chrono>

namespace Forgex::Core
{
	struct DeltaTimeHandler
	{
		std::chrono::steady_clock::time_point lastFrame = std::chrono::steady_clock::now();

		float Update()
		{
			const auto currentFrame = std::chrono::steady_clock::now();
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
		delete m_Window;
	}

	void Application::InitializeSystems()
	{
		Debug::Log::Init();

		m_Window = new Graphics::Window(1920, 1080, "Forgex Engine");
		m_InputManager.SetWindow(m_Window);

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
			m_InputManager.ConsumeEvents(m_LayerStack);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(deltaTime.Update());

			for (Layer* layer : m_LayerStack)
				layer->OnRender(m_SessionContext.GetViewportFramebuffer());

			m_Window->Update();

		} while (!m_Window->ShouldClose());

		for (Layer* layer : m_LayerStack)
			layer->OnEnd();
	}
}
