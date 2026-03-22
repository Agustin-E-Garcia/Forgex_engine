#include "EngineCore.h"
#include "DebugMacros.h"
#include <ForgexAssets.h>
#include <ForgexDebug.h>
#include <chrono>

namespace Forgex::Core
{
    struct DeltaTimeHandler
    {
        std::chrono::steady_clock::time_point lastFrame = std::chrono::steady_clock::now();

        float Update()
        {
            const auto currentFrame = std::chrono::steady_clock::now();
            const std::chrono::duration<float> delta = currentFrame - lastFrame;
            lastFrame = currentFrame;
            return delta.count();
        }
    };

    void EngineCore::Run()
    {
        Init();
        DeltaTimeHandler deltaTimeHandler;

        for(Layer::Layer* layer : m_LayerStack)
                layer->OnBegin();

        while (!m_Window->ShouldClose())
        {
            float deltaTime = deltaTimeHandler.Update();

            for(Layer::Layer* layer : m_LayerStack)
                layer->OnUpdate(deltaTime);

            for(Layer::Layer* layer : m_LayerStack)
                layer->OnRender();

            m_Window->Update();
        }

        for(Layer::Layer* layer : m_LayerStack)
                layer->OnEnd();

        Shutdown();
    }

    void EngineCore::Init()
    {
        m_DebugManager = new Debug::DebugManager();
        m_AssetManager = new Assets::AssetManager();

        ServiceLocator::Get().Register<Debug::DebugManager>(m_DebugManager);
        ServiceLocator::Get().Register<Assets::AssetManager>(m_AssetManager);

        // then all modules
        for (auto* m : m_ModuleRegistry)
            m->Init(*this);
    }

    void EngineCore::Shutdown()
    {
        for (auto* m : m_ModuleRegistry)
            m->Shutdown();

        delete m_AssetManager;
        delete m_DebugManager;
    }
}
