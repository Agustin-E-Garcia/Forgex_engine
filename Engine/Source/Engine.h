#pragma once
#include <ForgexCore.h>

namespace Forgex::Engine
{
    class Engine
    {
    public:
        Engine();
        ~Engine();

        void Run();

        void PushLayer(Core::Interfaces::ILayer* layer);
        void PushOverlay(Core::Interfaces::ILayer* overlay);

    private:
        Core::EngineCore* m_EngineCore;
    };
}
