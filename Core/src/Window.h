#pragma once
#include "Exports.h"
#include "Event/EventList.h"

class GLFWwindow;

class ENGINE_API Window
{
	using EventCallbackFn = std::function<void(Event&)>;

public:
	Window(int width, int height, char* title);
	~Window();

	void Update();
	bool ShouldClose();

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }

	inline GLFWwindow* GetNativeWindow() { return m_Window; }

	inline void SetEventCallback(const EventCallbackFn& callback) { m_EventCallback = callback; };
private:
	GLFWwindow* m_Window;
	
	int m_Width;
	int m_Height;

	EventCallbackFn m_EventCallback;
	void SetupEvents();
};