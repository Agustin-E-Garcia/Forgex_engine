#pragma once
#include <ForgexCore.h>
#include "UIWindowManager.h"

#include "Panels/Console.h"
#include "Panels/AssetInspector.h"
#include "Panels/Profiler.h"
#include "Panels/MaterialInspector.h"
#include "Panels/EntityInspector.h"
#include "Utils/ForgexToImGui.h"
#include "imgui.h"

namespace Forgex::Editor::UI
{
    class UIOverlay : public Core::Interfaces::ILayer
    {
    public:
        UIOverlay() : Core::Interfaces::ILayer("UI Overlay") {}

        void OnAttach() override {}

        void OnDetach() override {}

        void OnBegin() override
        {
            m_WindowManager = new UIWindowManager();

            m_ConsolePanelID = m_WindowManager->AddWindow<Panels::ConsolePanel>();
            m_AssetInspectorID = m_WindowManager->AddWindow<Panels::AssetManagerInspectorPanel>();
            m_ProfilerID = m_WindowManager->AddWindow<Panels::ProfilerPanel>();
            m_MaterialInspectorID = m_WindowManager->AddWindow<Panels::MaterialInspectorPanel>();
            m_EntityInspectorID = m_WindowManager->AddWindow<Panels::EntityInspectorPanel>();

            REGISTER_COMMAND("assets", [this](){ m_WindowManager->GetWindow<Panels::AssetManagerInspectorPanel>(m_AssetInspectorID)->ToggleWindow(); }, "Toggles the asset inspector");
            REGISTER_COMMAND("profiler", [this]() { m_WindowManager->GetWindow<Panels::ProfilerPanel>(m_ProfilerID)->ToggleWindow(); }, "Toggles the profiler");
            REGISTER_COMMAND("materials", [this]() { m_WindowManager->GetWindow<Panels::MaterialInspectorPanel>(m_MaterialInspectorID)->ToggleWindow(); }, "Toggles the material inspector");
            REGISTER_COMMAND("entities", [this]() { m_WindowManager->GetWindow<Panels::EntityInspectorPanel>(m_EntityInspectorID)->ToggleWindow(); }, "Toggles the Entity inspector");
        }

        void OnEnd() override { delete m_WindowManager; }

        void OnUpdate(float deltaTime) override
        {
            if(ImGui::IsKeyPressed(ImGuiKey_F1)) m_WindowManager->GetWindow<Panels::ConsolePanel>(m_ConsolePanelID)->ToggleWindow();

            if(ImGui::IsKeyPressed(ImGuiKey_Tab))
            {
                m_MouseLock = !m_MouseLock;
                Core::Layer::Event::MouseLockEvent event(m_MouseLock);

                m_CallbackFn(event);
            }

            m_WindowManager->Update(deltaTime);
        }

        void OnEvent(Core::Layer::Event::Event* event) override
        {
            Core::Layer::Event::EventDispatcher dispatcher(*event);
            dispatcher.Dispatch<Core::Layer::Event::KeyPressedEvent>(BIND_EVENT_FUNCTION(UIOverlay::HandleKeyPressedEvent));
            dispatcher.Dispatch<Core::Layer::Event::KeyReleasedEvent>(BIND_EVENT_FUNCTION(UIOverlay::HandleKeyReleasedEvent));
            dispatcher.Dispatch<Core::Layer::Event::MouseClickEvent>(BIND_EVENT_FUNCTION(UIOverlay::HandleMouseClickEvent));
            dispatcher.Dispatch<Core::Layer::Event::MousePositionEvent>(BIND_EVENT_FUNCTION(UIOverlay::HandleMousePositionEvent));
            dispatcher.Dispatch<Core::Layer::Event::CharInputEvent>(BIND_EVENT_FUNCTION(UIOverlay::HandleCharInputEvent));
            dispatcher.Dispatch<Core::Layer::Event::WindowResizedEvent>(BIND_EVENT_FUNCTION(UIOverlay::HandleWindowResizedEvent));
        }

        void OnRender() override { m_WindowManager->Render(); }

    private:
        UIWindowManager* m_WindowManager;
        bool m_WindowActive = true;

        bool m_MouseLock = true;

        unsigned int m_ConsolePanelID;
        unsigned int m_AssetInspectorID;
        unsigned int m_ProfilerID;
        unsigned int m_MaterialInspectorID;
        unsigned int m_EntityInspectorID;

        bool HandleKeyPressedEvent(Core::Layer::Event::KeyPressedEvent& event)
        {
            ImGui::GetIO().AddKeyEvent(Utils::ForgexKeyToImGuiKey(event.GetKeyCode()), event.IsPressed());
            return !m_MouseLock;
        }
        bool HandleKeyReleasedEvent(Core::Layer::Event::KeyReleasedEvent& event)
        {
            ImGui::GetIO().AddKeyEvent(Utils::ForgexKeyToImGuiKey(event.GetKeyCode()), false);
            return false;
        }
        bool HandleMouseClickEvent(Core::Layer::Event::MouseClickEvent& event)
        {
            if(m_MouseLock) return false;

            ImGui::GetIO().AddMouseButtonEvent(event.GetButton(), event.IsPressed());
            return true;
        }
        bool HandleMousePositionEvent(Core::Layer::Event::MousePositionEvent& event)
        {
            if(m_MouseLock) return false;

            ImGui::GetIO().AddMousePosEvent(event.GetPositionX(), event.GetPositionY());
            return true;
        }
        bool HandleCharInputEvent(Core::Layer::Event::CharInputEvent& event)
        {
            if(m_MouseLock) return false;

            ImGui::GetIO().AddInputCharacter(event.GetKeyCode());
            return true;
        }
        bool HandleWindowResizedEvent(Core::Layer::Event::WindowResizedEvent& event)
        {
            m_WindowActive = event.GetWidth() > 0 && event.GetHeight() > 0;
            if (!m_WindowActive) return true;

            ImGui::GetIO().DisplaySize = ImVec2(event.GetWidth(), event.GetHeight());
            return true;
        }
    };
}
