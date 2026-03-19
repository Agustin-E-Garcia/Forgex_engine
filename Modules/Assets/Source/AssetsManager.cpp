#include "AssetsManager.h"

namespace Forgex::Assets
{
    AssetManager& AssetManager::Get()
    {
        static AssetManager instance;
        return instance;
    }

    const std::unordered_map<std::string, Asset*>& AssetManager::GetLoadedAssets() const
    {
        return m_LoadedAssets;
    }
}
