#include "VoxelModule.h"
#include "Systems/VoxelMapSetupSystem.h"
#include "Systems/VoxelTerrainSystem.h"

namespace Forgex::Voxel
{
    void VoxelModule::Init(Core::EngineCore& core)
    {
        core.RegisterSystem<Systems::VoxelMapSetupSystem>();
        core.RegisterSystem<Systems::VoxelTerrainSystem>();
    }

    void VoxelModule::Shutdown() {}
}
