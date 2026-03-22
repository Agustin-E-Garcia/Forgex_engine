#pragma once
#include <ForgexCore.h>

namespace Forgex::Scene
{
    class SceneModule : public Core::Interfaces::IModule
    {
    public:
        void Init(Core::EngineCore& core) override;
        void Shutdown() override;

        const char* GetName() const override { return "Scene_Module"; }
    };
}
