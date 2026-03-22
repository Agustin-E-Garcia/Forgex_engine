#pragma once
#include <ForgexCore.h>

struct GLFWwindow;

namespace Forgex::Graphics
{
    class Window : public Core::Interfaces::IWindow
    {
    public:
        Window(int width, int height, const char* title);
        ~Window();

        void Update() override;
        bool ShouldClose() const override;
        void SetEventCallback(const Core::Interfaces::IWindow::EventCallbackFn& callback) override { m_EventCallback = callback; }

    private:
        GLFWwindow* m_Window;
        Core::Interfaces::IWindow::EventCallbackFn m_EventCallback;
    };
}
