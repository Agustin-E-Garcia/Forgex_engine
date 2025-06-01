#pragma once
#include "GraphicsExports.h"
#include <functional>

struct GLFWwindow;

namespace Forgex::Graphics
{
	class Event;

	using WindowResizedCallbackFn = std::function<void(float width, float height)>;
	using KeyPressedCallbackFn = std::function<void(unsigned int keycode, bool repeat, bool pressed)>;
	using CharInputCallbackFn = std::function<void(unsigned int keycode)>;
	using MouseMoveCallbackFn = std::function<void(float MouseX, float MouseY)>;
	using MouseWheelCallbackFn = std::function<void(double xOffset, double yOffset)>;
	using MouseClickedCallbackFn = std::function<void(unsigned int button, bool clicked)>;

	class GRAPHICS_API Window
	{
	public:
		Window(int width, int height, const char* title);
		~Window();

		void Update();
		bool ShouldClose();

		inline int GetWidth() const { return m_Width; }
		inline int GetHeight() const { return m_Height; }

		inline GLFWwindow* GetNativeWindow() { return m_Window; }

		void RegisterWindowResizeCallback(const WindowResizedCallbackFn& callback) { m_WindowResizeCallback = callback; }
		void RegisterKeyPressedCallback(const KeyPressedCallbackFn& callback) { m_KeyPressedCallback = callback; }
		void RegisterCharInputCallback(const CharInputCallbackFn& callback) { m_CharInputCallback = callback; }
		void RegisterMouseMoveCallback(const MouseMoveCallbackFn& callback) { m_MouseMoveCallback = callback; }
		void RegisterMouseWheelCallback(const MouseWheelCallbackFn& callback) { m_MouseWheelCallback = callback; }
		void RegisterMouseClickedCallback(const MouseClickedCallbackFn& callback) { m_MouseClickedCallback = callback; }

	private:
		GLFWwindow* m_Window;
	
		int m_Width;
		int m_Height;


		// Events code
		void SetupEvents();
		WindowResizedCallbackFn m_WindowResizeCallback;
		KeyPressedCallbackFn m_KeyPressedCallback;
		CharInputCallbackFn m_CharInputCallback;
		MouseMoveCallbackFn m_MouseMoveCallback;
		MouseWheelCallbackFn m_MouseWheelCallback;
		MouseClickedCallbackFn m_MouseClickedCallback;
	};
}
