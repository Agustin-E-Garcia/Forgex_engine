#pragma once
#include "Exports.h"
#include "Window.h"
#include "Layer/LayerStack.h"
#include "Profiler.h"

class Renderer;
class GameLayer;

class ENGINE_API Application 
{
public:
	Application();
	~Application();

	void InitializeSystems();
	void HandleEvents(Event& event);
	void Run();

	void PushLayer(Layer* layer);
	void PushOverlay(Layer* layer);

	static inline void* GetWindowPtr() { return s_Instance->m_Window->GetNativeWindow(); }

private:
	static Application* s_Instance;

	Window* m_Window;
	Renderer* m_Renderer;

	LayerStack m_LayerStack;
	GameLayer* m_GameLayer;

	bool m_ShouldClose;

	bool OnWindowClose(WindowCloseEvent& e);
};