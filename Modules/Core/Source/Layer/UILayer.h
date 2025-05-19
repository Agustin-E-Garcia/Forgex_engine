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

            dispatcher.Dispatch<MousePositionEvent>(BIND_EVENT_FUNCTION(UILayer::HandleMousePositionEvent));
            dispatcher.Dispatch<MouseClickEvent>(BIND_EVENT_FUNCTION(UILayer::HandleMouseClickedEvent));
        }

        void OnRender() override { m_WindowManager->Render(); }

    private:
        UI::UIWindowManager* m_WindowManager = nullptr;

        bool HandleMousePositionEvent(MousePositionEvent& event) {}
        bool HandleMouseClickedEvent(MouseClickEvent& event) {}
    };
}