#include "Window.h"
#include <GLFW/glfw3.h>

namespace Forgex::Graphics
{
    Window::Window(int width, int height, const char* title)
    {
        if (!glfwInit()) LOG_CORE(Debug::LogLevel::Critical, "Failed to initialize GLFW");

        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);
        //glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

        m_Window = glfwCreateWindow(width, height, title, NULL, NULL);
        if (m_Window == NULL) LOG_CORE(Debug::LogLevel::Critical, "Failed to open GLFW window");

        glfwGetWindowSize(m_Window, &m_Width, &m_Height);
        glfwMakeContextCurrent(m_Window);

        LOG_CORE(Debug::LogLevel::Info, "Window '{0}' created successfully", title);
    }

    Window::~Window()
    {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    void Window::Update()
    {
        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }

    bool Window::ShouldClose() const
    {
        return glfwWindowShouldClose(m_Window);
    }
}
