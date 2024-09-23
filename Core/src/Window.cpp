#include "Window.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Log.h"

#define GET_DISPATCHER EventDispatcher dispatcher = *(EventDispatcher*)glfwGetWindowUserPointer(window);

Window::Window(int width, int height, char* title) : m_Width(width), m_Height(height)
{
	if (!glfwInit()) LOG_CORE_CRITICAL("Failed to initialize GLFW");

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_Window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (m_Window == NULL) LOG_CORE_CRITICAL("Failed to open GLFW window");

	glfwMakeContextCurrent(m_Window);
	glewExperimental = true;
	if (glewInit() != GLEW_OK) LOG_CORE_CRITICAL("Failed to initialize GLEW");

	SetupEvents();

	LOG_CORE_INFO("Window '{0}' created successfully", title);
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
	glfwSetWindowUserPointer(m_Window, &m_EventCallback);
	glfwSetInputMode(m_Window, GLFW_STICKY_KEYS, GLFW_TRUE);

	glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			EventCallbackFn& callback = *(EventCallbackFn*)glfwGetWindowUserPointer(window);
			WindowResizedEvent e(width, height);
			callback(e);
		});

	glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) 
		{
			EventCallbackFn& callback = *(EventCallbackFn*)glfwGetWindowUserPointer(window);
			WindowCloseEvent e;
			callback(e);
		});

	glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int keyCode, int scancode, int action, int mods)
		{
			EventCallbackFn& callback = *(EventCallbackFn*)glfwGetWindowUserPointer(window);
			
			switch (action)
			{
				case GLFW_PRESS:
				case GLFW_REPEAT:
				{
					KeyPressedEvent e(keyCode, action == GLFW_REPEAT);
					callback(e);
					break;
				}
				case GLFW_RELEASE: 
				{
					KeyReleasedEvent e(keyCode);
					callback(e);
					break;
				}
			}
		});

	glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
			EventCallbackFn& callback = *(EventCallbackFn*)glfwGetWindowUserPointer(window);
			MousePositionEvent e(xPos, yPos);
			callback(e);
		});

	glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			EventCallbackFn& callback = *(EventCallbackFn*)glfwGetWindowUserPointer(window);
			
			switch (action)
			{
				case GLFW_PRESS: 
				{
					MouseClickEvent e(button);
					callback(e);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseUnclickEvent e(button);
					callback(e);
					break;
				}
			}
		});
}