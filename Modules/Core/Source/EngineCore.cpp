#include "EngineCore.h"
#include "ServiceLocator.h"
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
        m_Window->SetEventCallback([this](Layer::Event::Event& event) { m_LayerStack.OnEvent(event); });
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
        ServiceLocator::Get().Register<Debug::DebugManager>();
        ServiceLocator::Get().Register<Assets::AssetManager>();

        // then all modules
        for (auto& [ index, module ] : m_ModuleRegistry)
            module->Init(*this);
    }

    void EngineCore::Shutdown()
    {
        for (auto& [ index, module ] : m_ModuleRegistry)
            module->Shutdown();
    }
}
