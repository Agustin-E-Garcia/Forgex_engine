#include "VoxelModule.h"
#include <ForgexCore.h>

#include "VoxelSettings.h"
#include "Systems/ChunkManagementSystem.h"
#include "Systems/VoxelTerrainSystem.h"

namespace Forgex::Voxel
{
    void VoxelModule::Init(Core::EngineCore& core)
    {
        GET_SERVICE(Core::Settings::ProjectSettings)->RegisterSettings<VoxelSettings>();

        core.RegisterSystem<Systems::ChunkManagementSystem>();
        core.RegisterSystem<Systems::VoxelTerrainSystem>();
    }

    void VoxelModule::Shutdown() {}
}
