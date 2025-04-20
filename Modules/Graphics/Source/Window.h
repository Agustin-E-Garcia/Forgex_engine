#pragma once
#include "GraphicsExports.h"

struct GLFWwindow;

namespace Forgex::Graphics
{
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
	private:
		GLFWwindow* m_Window;
	
		int m_Width;
		int m_Height;
	};	
}