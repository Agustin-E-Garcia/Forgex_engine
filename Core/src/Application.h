#pragma once
#include "Exports.h"
#include "Window.h"
#include "Layer/LayerStack.h"

class Renderer;
class Scene;
class Camera;

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

	template<class T>
	T* GetLayerOfType() 
	{
		static_assert(std::is_base_of<Layer, T>::value, "T must inherit from Layer");
		return m_LayerStack.GetLayerOfType<T>();
	}

	Scene* GetActiveScene();

	static inline void* GetNativeWindowPtr() { return s_Instance->m_Window->GetNativeWindow(); }
	static void SetActiveCamera(Camera* camera);

	static inline const Window* GetWindow() { return s_Instance->m_Window; }
	static inline const Renderer* GetRenderer() { return s_Instance->m_Renderer; }

private:
	static Application* s_Instance;

	Window* m_Window;
	Renderer* m_Renderer;

	LayerStack m_LayerStack;

	bool m_ShouldClose;

	bool OnWindowClose(WindowCloseEvent& e);
};