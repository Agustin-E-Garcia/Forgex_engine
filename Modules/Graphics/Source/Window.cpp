#include "Window.h"
#include <ForgexDebugTools.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Forgex::Graphics
{
	Window::Window(int width, int height, const char* title) : m_Width(width), m_Height(height)
	{
		if (!glfwInit()) LOG_CORE(Debug::LogLevel::Critical, "Failed to initialize GLFW");

		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);
		//glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

		m_Window = glfwCreateWindow(m_Width, m_Height, title, NULL, NULL);
		if (m_Window == NULL) LOG_CORE(Debug::LogLevel::Critical, "Failed to open GLFW window");

		glfwGetWindowSize(m_Window, &m_Width, &m_Height);

		glfwMakeContextCurrent(m_Window);
		glewExperimental = true;
		if (glewInit() != GLEW_OK) LOG_CORE(Debug::LogLevel::Critical, "Failed to initialize GLEW");
		
		SetupEvents();

		LOG_CORE(Debug::LogLevel::Info, "Window '{0}' created successfully", title);
	}

	Window::~Window() 
	{
		glfwTerminate();
	}

	void Window::Update()
	{
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

	bool Window::ShouldClose()
	{
		return glfwWindowShouldClose(m_Window);
	}

	void Window::SetupEvents()
	{
		glfwSetWindowUserPointer(m_Window, this);
		glfwSetInputMode(m_Window, GLFW_STICKY_KEYS, GLFW_TRUE);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				Window* wind = (Window*)glfwGetWindowUserPointer(window);
				wind->m_WindowResizeCallback(width, height);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int keyCode, int scancode, int action, int mods)
			{
				Window* wind = (Window*)glfwGetWindowUserPointer(window);
				wind->m_KeyPressedCallback(keyCode, action == GLFW_REPEAT, action != GLFW_RELEASE);
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int codepoint)
			{
				Window* wind = (Window*)glfwGetWindowUserPointer(window);
				wind->m_CharInputCallback(codepoint);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				Window* wind = (Window*)glfwGetWindowUserPointer(window);
				wind->m_MouseMoveCallback(xPos, yPos);
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				Window* wind = (Window*)glfwGetWindowUserPointer(window);
				wind->m_MouseClickedCallback(button, action == GLFW_PRESS);
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
			{
				Window* wind = (Window*)glfwGetWindowUserPointer(window);
				wind->m_MouseWheelCallback(xoffset, yoffset);
			});
	}
}
