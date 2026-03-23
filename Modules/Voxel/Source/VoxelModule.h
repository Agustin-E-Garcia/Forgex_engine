#pragma once
#include <ForgexCore.h>

namespace Forgex::Voxel
{
    class VoxelModule : public Core::Interfaces::IModule
    {
    public:
        void Init(Core::EngineCore& core) override;
        void Shutdown() override;

        const char* GetName() const override { return "Voxel_Module"; }
   };
}
