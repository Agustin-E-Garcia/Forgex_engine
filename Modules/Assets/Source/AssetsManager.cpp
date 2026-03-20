#include "AssetsManager.h"
#include <algorithm>

namespace Forgex::Assets
{
    AssetManager& AssetManager::Get()
    {
        static AssetManager instance;
        return instance;
    }

    const std::unordered_map<int, Asset*>& AssetManager::GetLoadedAssets() const
    {
        return m_LoadedAssets;
    }

    Asset* AssetManager::GetAsset(int id)
    {
        if(IsIDValid(id)) return m_LoadedAssets[id];
        return nullptr;
    }

    bool AssetManager::IsIDValid(int id) const { return m_LoadedAssets.contains(id); }

    void AssetManager::UnloadAsset(int assetID)
    {
        if(!m_LoadedAssets.contains(assetID)) return;

        delete m_LoadedAssets[assetID];
        m_LoadedAssets.erase(assetID);

        auto it = std::find_if(m_AssetPathToID.begin(), m_AssetPathToID.end(),
            [assetID](const auto& pair) { return pair.second == assetID; });

        if(it != m_AssetPathToID.end()) m_AssetPathToID.erase(it);
    }
}
