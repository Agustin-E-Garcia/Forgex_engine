#pragma once
#include <ForgexCore.h>

namespace Forgex::Engine
{
    class Engine
    {
    public:
        Engine();
        ~Engine();

        void PushLayer(Core::Layer::Layer* layer);
        void PushOverlay(Core::Layer::Layer* overlay);

    private:
        Core::EngineCore* m_EngineCore;
    };
}
