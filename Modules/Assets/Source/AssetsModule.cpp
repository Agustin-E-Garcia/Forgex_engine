#include "AssetsModule.h"
#include "AssetsManager.h"

namespace Forgex::Assets
{
    void AssetsModule::Init(Core::EngineCore &core)
    {
        Core::ServiceLocator::Get().Register<AssetManager>();
    }

    void AssetsModule::Shutdown() {}
}
