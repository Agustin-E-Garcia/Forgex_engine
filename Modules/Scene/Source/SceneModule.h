#pragma once
#include "SceneExports.h"
#include <ForgexCore.h>

namespace Forgex::Scene
{
    class SCENE_API SceneModule : public Core::Interfaces::IModule
    {
    public:
        void Init(Core::EngineCore& core) override;
        void Shutdown() override;

        const char* GetName() const override { return "Scene_Module"; }
    };
}
