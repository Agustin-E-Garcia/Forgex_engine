#include "EngineCore.h"
#include "DebugMacros.h"
#include "Layer/Event/EventList.h"
#include "ServiceLocator.h"
#include "JobManager.h"
#include <ForgexDebug.h>
#include <ForgexFiles.h>
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

        for(Interfaces::ILayer* layer : m_LayerStack)
                layer->OnBegin();

        while (!m_Window->ShouldClose())
        {
            float deltaTime = deltaTimeHandler.Update();

            for(Interfaces::ILayer* layer : m_LayerStack)
                layer->OnUpdate(deltaTime);

            for(Interfaces::ILayer* layer : m_LayerStack)
                layer->OnRender();

            m_Window->Update();
        }

        for(Interfaces::ILayer* layer : m_LayerStack)
                layer->OnEnd();

        Shutdown();
    }

    void EngineCore::Init()
    {
        ServiceLocator::Get().Register<Debug::DebugManager>();

        ServiceLocator::Get().Register<JobManager>(1);

        // then all modules
        for (auto& [ index, module ] : m_ModuleRegistry)
            module->Init(*this);

        m_Window->SetEventCallback(BIND_EVENT_FUNCTION(EngineCore::OnEvent));
        m_LayerStack.SetEventCallback(BIND_EVENT_FUNCTION(EngineCore::OnEvent));
    }

    void EngineCore::Shutdown()
    {
        for (auto& [ index, module ] : m_ModuleRegistry)
            module->Shutdown();
    }

    void EngineCore::OnEvent(Layer::Event::Event& event)
    {
        Layer::Event::EventDispatcher dispatcher(event);
        dispatcher.Dispatch<Layer::Event::MouseLockEvent>([this](Layer::Event::MouseLockEvent& event)->bool { m_Window->SetMouseLock(event.GetState()); return true;});

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
        {
            (*--it)->OnEvent(&event);
            if (event.m_Handled) break;
        }
    }
}
