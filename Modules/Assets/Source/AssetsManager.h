#pragma once
#include "Asset.h"
#include <unordered_map>
#include <string>
#include <utility>

namespace Forgex::Assets
{
    template<class T> class AssetHandle;

    class AssetManager
    {
    public:
        AssetManager();
        ~AssetManager();

        template<class T, typename... Args>
        AssetHandle<T> LoadAsset(const std::string& assetPath, Args&&... args)
        {
            static_assert(std::is_base_of<Asset, T>::value, "T must inherit from Asset");

            if(m_AssetPathToID.contains(assetPath)) { return AssetHandle<T>(this, m_AssetPathToID[assetPath]); }

            Asset* newAsset = new T(assetPath, std::forward<Args>(args)...);
            if(!newAsset->Load())
            {
                delete newAsset;
                return AssetHandle<T>();
            }

            int newID = m_IDCounter++;
            m_AssetPathToID[assetPath] = newID;
            m_LoadedAssets[newID] = newAsset;

            return AssetHandle<T>(this, newID);
        }

        void UnloadAsset(int assetID);

        const std::unordered_map<int, Asset*>& GetLoadedAssets() const;
        Asset* GetAsset(int id);
        bool IsIDValid(int id) const;

    private:
        std::unordered_map<std::string, int> m_AssetPathToID;
        std::unordered_map<int, Asset*> m_LoadedAssets;
        int m_IDCounter = 0;
    };
}
