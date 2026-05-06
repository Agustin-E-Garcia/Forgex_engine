#pragma once
#include "EngineExports.h"
#include <ForgexCore.h>

namespace Forgex::Engine
{
    class ENGINE_API Engine
    {
    public:
        Engine();
        ~Engine();

        void Run();

        void PushLayer(Core::Interfaces::ILayer* layer);
        void PushOverlay(Core::Interfaces::ILayer* overlay);

        template<typename T>
        void RegisterSystem()
        {
            m_EngineCore->RegisterSystem<T>();
        }

    private:
        Core::EngineCore* m_EngineCore;
    };
}
