#pragma once
#include "AssetsExports.h"
#include <ForgexCore.h>

namespace Forgex::Assets
{
    class ASSETS_API AssetsModule : public Core::Interfaces::IModule
    {
    public:
        void Init(Core::EngineCore &core) override;
        void Shutdown() override;

        const char* GetName() const override { return "Assets_Module"; }
    };
}
