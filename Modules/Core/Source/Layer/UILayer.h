#pragma once
#include "Layer.h"
#include <ForgexUI.h>

#include <ForgexDebugTools.h>

namespace Forgex::Core
{
	class CORE_API Viewport : public UI::GUIWindow
	{
		using ViewportResizeCallbackFn = std::function<void(float width, float height)>;
	public:
		Viewport(unsigned int viewportFramebufferID, ViewportResizeCallbackFn callback) : UI::GUIWindow("Viewport", true),
			m_ViewportFramebuffer(viewportFramebufferID), m_Callback(callback) {}
		~Viewport() {}
	protected:
		virtual void OnDraw() override 
		{
			float w, h;
			UI::Elements::GetAvailableContentSize(w, h);
			m_Callback(w, h);

			UI::Elements::Image(m_ViewportFramebuffer, w, h); 
		}
	private:
		unsigned int m_ViewportFramebuffer;
		ViewportResizeCallbackFn m_Callback;
	};

    class UILayer : public Layer
    {
    public:
        UILayer() : Layer("UI") {}

        ~UILayer() override { delete m_WindowManager; }

        void OnAttach() override { m_WindowManager = UI::CreateWindowManager(); }

        void OnDetach() override {}

        void OnBegin(SessionContext& sessionContext) override 
	{
		m_WindowManager->AddWindow<Viewport>(sessionContext.GetViewportID(),
				[&sessionContext](float width, float height)
				{ 
					sessionContext.ResizeViewportFramebuffer(width, height); 
				});
	}

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

        void OnRender(SessionContext& sessionContext) override { m_WindowManager->Render(); }

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
