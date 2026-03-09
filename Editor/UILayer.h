#pragma once
#include <ForgexCore.h>
#include "UI/UIWindowManager.h"

#include <ForgexDebugTools.h>

namespace Forgex::UI
{
    class UILayer : public Core::Layer
    {
    public:
        UILayer() : Layer("UI") {}

        ~UILayer() override { delete m_WindowManager; }

        void OnAttach() override { m_WindowManager = UI::CreateWindowManager(); }

        void OnDetach() override {}

        void OnBegin() override {}

        void OnEnd() override {}

        void OnUpdate(float deltaTime) override 
        {
            m_WindowManager->Update(deltaTime); 
        }

        void OnEvent(Core::Event* event) override
        {
            Core::EventDispatcher dispatcher(*event);

            dispatcher.Dispatch<Core::CharInputEvent>(BIND_EVENT_FUNCTION(UILayer::HandleCharInputEvent));
            dispatcher.Dispatch<Core::KeyPressedEvent>(BIND_EVENT_FUNCTION(UILayer::HandleKeyPressedEvent));
            dispatcher.Dispatch<Core::MousePositionEvent>(BIND_EVENT_FUNCTION(UILayer::HandleMousePositionEvent));
            dispatcher.Dispatch<Core::MouseWheelScrollEvent>(BIND_EVENT_FUNCTION(UILayer::HandleMouseWheelScrollEvent));
            dispatcher.Dispatch<Core::MouseClickEvent>(BIND_EVENT_FUNCTION(UILayer::HandleMouseClickedEvent));
            dispatcher.Dispatch<Core::WindowResizedEvent>(BIND_EVENT_FUNCTION(UILayer::HandleWindowResizedEvent));
        }

        void OnRender() override { m_WindowManager->Render(); }

    private:
        UI::UIWindowManager* m_WindowManager = nullptr;

        bool HandleCharInputEvent(Core::CharInputEvent& event) { m_WindowManager->OnCharInput(event.GetKeyCode()); return false; }
        bool HandleKeyPressedEvent(Core::KeyPressedEvent& event) { m_WindowManager->OnKeyPressed(event.GetKeyCode(), event.IsRepeat(), event.IsPressed()); return false; }
        bool HandleMousePositionEvent(Core::MousePositionEvent& event) { m_WindowManager->UpdateMousePosition(event.GetPositionX(), event.GetPositionY()); return false; }
        bool HandleMouseWheelScrollEvent(Core::MouseWheelScrollEvent& event) { m_WindowManager->OnMouseWheelScroll(event.GetXOffset(), event.GetYOffset()); return false; }
        bool HandleMouseClickedEvent(Core::MouseClickEvent& event) { m_WindowManager->OnMouseClick(event.GetButton(), event.IsPressed()); return false; }
        bool HandleWindowResizedEvent(Core::WindowResizedEvent& event) { m_WindowManager->OnWindowResized(event.GetWidth(), event.GetHeight()); return false; }
    };
}
