#include "Window.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Log.h"

Window::Window(int width, int height, char* title) 
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