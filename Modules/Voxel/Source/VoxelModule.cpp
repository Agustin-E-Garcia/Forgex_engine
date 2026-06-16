#include "VoxelModule.h"
#include <ForgexCore.h>

#include "VoxelSettings.h"
#include "Systems/VoxelMapSetupSystem.h"
#include "Systems/VoxelTerrainSystem.h"

namespace Forgex::Voxel
{
    void VoxelModule::Init(Core::EngineCore& core)
    {
        GET_SERVICE(Core::Settings::ProjectSettings)->RegisterSettings<VoxelSettings>();

        core.RegisterSystem<Systems::VoxelMapSetupSystem>();
        core.RegisterSystem<Systems::VoxelTerrainSystem>();
    }

    void VoxelModule::Shutdown() {}
}
