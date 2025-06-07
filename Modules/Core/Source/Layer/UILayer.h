#pragma once
#include "Layer.h"
#include <ForgexUI.h>

namespace Forgex::Core
{
    class UILayer : public Layer
    {
    public:
        UILayer() : Layer("UI") {}

        ~UILayer() override { delete m_WindowManager; }

        void OnAttach() override { m_WindowManager = UI::CreateWindowManager(); }

        void OnDetach() override {}

        void OnBegin() override {}

        void OnEnd() override {}

        void OnUpdate(float deltaTime) override { m_WindowManager->Update(deltaTime); }

        void OnEvent(Event* event) override
        {
            EventDispatcher dispatcher(*event);

            dispatcher.Dispatch<CharInputEvent>(BIND_EVENT_FUNCTION(UILayer::HandleCharInputEvent));
            dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FUNCTION(UILayer::HandleKeyPressedEvent));
            dispatcher.Dispatch<MousePositionEvent>(BIND_EVENT_FUNCTION(UILayer::HandleMousePositionEvent));
            dispatcher.Dispatch<MouseWheelScrollEvent>(BIND_EVENT_FUNCTION(UILayer::HandleMouseWheelScrollEvent));
            dispatcher.Dispatch<MouseClickEvent>(BIND_EVENT_FUNCTION(UILayer::HandleMouseClickedEvent));
            dispatcher.Dispatch<WindowResizedEvent>(BIND_EVENT_FUNCTION(UILayer::HandleWindowResizedEvent));
        }

        void OnRender(const Graphics::Resources::Framebuffer* framebuffer) override { m_WindowManager->Render(); }

    private:
        UI::UIWindowManager* m_WindowManager = nullptr;

        bool HandleCharInputEvent(CharInputEvent& event) { m_WindowManager->OnCharInput(event.GetKeyCode()); return false; }
        bool HandleKeyPressedEvent(KeyPressedEvent& event) { m_WindowManager->OnKeyPressed(event.GetKeyCode(), event.IsRepeat(), event.IsPressed()); return false; }
        bool HandleMousePositionEvent(MousePositionEvent& event) { m_WindowManager->UpdateMousePosition(event.GetPositionX(), event.GetPositionY()); return false; }
        bool HandleMouseWheelScrollEvent(MouseWheelScrollEvent& event) { m_WindowManager->OnMouseWheelScroll(event.GetXOffset(), event.GetYOffset()); return false; }
        bool HandleMouseClickedEvent(MouseClickEvent& event) { m_WindowManager->OnMouseClick(event.GetButton(), event.IsPressed()); return false; }
        bool HandleWindowResizedEvent(WindowResizedEvent& event) { m_WindowManager->OnWindowResized(event.GetWidth(), event.GetHeight()); return false; }
    };
}
