#pragma once
#include <ForgexCore.h>

namespace Forgex::Graphics
{
    class GraphicsModule : public Core::Interfaces::IModule
    {
    public:
        void Init(Core::EngineCore& core) override;
        void Update(float deltatime) override;
        void Shutdown() override;

        const char* GetName() const override { return "Graphics_Module"; }
    };
}
