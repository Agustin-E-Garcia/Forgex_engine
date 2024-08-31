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

	inline unsigned int GetWidth() const { return m_Width; }
	inline unsigned int GetHeight() const { return m_Height; }

	inline GLFWwindow* GetNativeWindow() { return m_Window; }

	inline void SetEventCallback(const EventCallbackFn& callback) { m_EventCallback = callback; };
private:
	GLFWwindow* m_Window;
	
	unsigned int m_Width;
	unsigned int m_Height;

	EventCallbackFn m_EventCallback;
	void SetupEvents();
};