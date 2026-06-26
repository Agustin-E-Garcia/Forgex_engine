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
        glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

        m_Window = glfwCreateWindow(width, height, title, NULL, NULL);
        if (m_Window == NULL) LOG_CORE(Debug::LogLevel::Critical, "Failed to open GLFW window");

        glfwGetWindowSize(m_Window, &m_Width, &m_Height);
        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, this);
        SetMouseLock(true);

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            Window& self = *(Window*)glfwGetWindowUserPointer(window);
            switch (action)
            {
                case GLFW_PRESS:
                case GLFW_REPEAT:
                {
                    Core::Layer::Event::KeyPressedEvent event(key, action == GLFW_REPEAT, true);
                    self.m_EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    Core::Layer::Event::KeyReleasedEvent event(key);
                    self.m_EventCallback(event);
                    break;
                }
            }
        });

        glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int codepoint)
        {
            Window& self = *(Window*)glfwGetWindowUserPointer(window);
            Core::Layer::Event::CharInputEvent event(codepoint);
            self.m_EventCallback(event);
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
        {
            Window& self = *(Window*)glfwGetWindowUserPointer(window);
            Core::Layer::Event::MouseClickEvent event(button, action == GLFW_PRESS);
            self.m_EventCallback(event);
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
        {
            Window& self = *(Window*)glfwGetWindowUserPointer(window);
            Core::Layer::Event::MousePositionEvent event(xpos, ypos);
            self.m_EventCallback(event);
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
        {
            Window& self = *(Window*)glfwGetWindowUserPointer(window);
            Core::Layer::Event::MouseWheelScrollEvent event(xoffset, yoffset);
            self.m_EventCallback(event);
        });

        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
        {
            Window& self = *(Window*)glfwGetWindowUserPointer(window);
            Core::Layer::Event::WindowResizedEvent event(width, height);
            self.m_EventCallback(event);
        });

        LOG_CORE(Debug::LogLevel::Info, "Window '{0}' created successfully", title);
    }

    Window::~Window()
    {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    void Window::Update()
    {
        PROFILE_FUNCTION("Window Update");
        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }

    bool Window::ShouldClose() const
    {
        return glfwWindowShouldClose(m_Window);
    }

    void Window::SetMouseLock(bool newState)
    {
        if (newState) glfwSetCursorPos(m_Window, m_Width / 2.0, m_Height / 2.0);
        glfwSetInputMode(m_Window, GLFW_CURSOR, newState ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
    }
}
