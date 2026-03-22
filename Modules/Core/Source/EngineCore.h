#pragma once
#include "Registry.h"
#include "Interfaces/IWindow.h"
#include "Interfaces/IModule.h"
#include "Interfaces/ISystem.h"
#include "Layer/LayerStack.h"

namespace Forgex::Core
{
    class EngineCore
    {
    public:
        void Run();

        void SetWindow(Interfaces::IWindow* window) { m_Window = window; }

        template<class T>
        void RegisterModule() { m_ModuleRegistry.Register<T>(); }
        template<class T>
        void RegisterSystem() { m_SystemRegistry.Register<T>(); }

        void RegisterLayer(Layer::Layer* layer) { m_LayerStack.PushLayer(layer); }
        void RegisterOverlay(Layer::Layer* overlay) { m_LayerStack.PushOverlay(overlay); }

        Interfaces::IWindow* GetWindow() const { return m_Window; }
        Registry<Interfaces::IModule>& GetModuleRegistry() { return m_ModuleRegistry; }
        Registry<Interfaces::ISystem>& GetSystemRegistry() { return m_SystemRegistry; }

    private:
        void Init();
        void Shutdown();

        Interfaces::IWindow* m_Window;
        Registry<Interfaces::IModule> m_ModuleRegistry;
        Registry<Interfaces::ISystem> m_SystemRegistry;
        Layer::LayerStack m_LayerStack;
    };
}
