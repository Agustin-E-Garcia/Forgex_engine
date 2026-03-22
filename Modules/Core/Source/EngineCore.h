#pragma once
#include "Registries/ModuleRegistry.h"
#include "Registries/SystemRegistry.h"
#include "Interfaces/IWindow.h"
#include "Layer/LayerStack.h"

namespace Forgex::Assets { class AssetManager; }
namespace Forgex::Debug { class DebugManager; }

namespace Forgex::Core
{
    class EngineCore
    {
    public:
        void Run();

        void SetWindow(Interfaces::IWindow* window) { m_Window = window; }

        void RegisterModule(Interfaces::IModule* module) { m_ModuleRegistry.RegisterModule(module); }
        void RegisterSystem(Interfaces::ISystem* system) { m_SystemRegistry.registerSystem(system); }

        void RegisterLayer(Layer::Layer* layer) { m_LayerStack.PushLayer(layer); }
        void RegisterOverlay(Layer::Layer* overlay) { m_LayerStack.PushOverlay(overlay); }

        Interfaces::IWindow* GetWindow() const { return m_Window; }
        Registries::ModuleRegistry GetModuleRegistry() { return m_ModuleRegistry; }
        Registries::SystemRegistry GetSystemRegistry() { return m_SystemRegistry; }

    private:
        void Init();
        void Shutdown();

        Assets::AssetManager* m_AssetManager;
        Debug::DebugManager* m_DebugManager;

        Interfaces::IWindow* m_Window;
        Registries::ModuleRegistry m_ModuleRegistry;
        Registries::SystemRegistry m_SystemRegistry;
        Layer::LayerStack m_LayerStack;
    };
}
