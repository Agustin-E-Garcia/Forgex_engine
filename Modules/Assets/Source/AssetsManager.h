#pragma once
#include "AssetsExports.h"
#include "Asset.h"
#include <unordered_map>
#include <string>

namespace Forgex::Assets
{
    template<class T> class AssetHandle;
    class Asset;

    class ASSETS_API AssetManager
    {
    public:
        static AssetManager& Get();

        const std::unordered_map<int, Asset*>& GetLoadedAssets() const;
        Asset* GetAsset(int id);
        bool IsIDValid(int id) const;

        template<class T>
        AssetHandle<T> LoadAsset(const std::string& assetPath)
        {
            static_assert(std::is_base_of<Asset, T>::value, "T must inherit from Asset");

            if(m_AssetPathToID.contains(assetPath)) { return AssetHandle<T>(m_AssetPathToID[assetPath]); }

            Asset* newAsset = new T(assetPath);
            if(!newAsset->Load())
            {
                delete newAsset;
                return AssetHandle<T>(-1);
            }

            int newID = m_IDCounter++;
            m_AssetPathToID[assetPath] = newID;
            m_LoadedAssets[newID] = newAsset;

            return AssetHandle<T>(newID);
        }

        void UnloadAsset(int assetID);

    private:
        AssetManager() = default;
        AssetManager(const AssetManager&) = delete;
        AssetManager& operator=(const AssetManager&) = delete;

        ~AssetManager() 
        { 
            for(auto& [id, asset] : m_LoadedAssets) 
                delete asset; 
        }

        std::unordered_map<std::string, int> m_AssetPathToID;
        std::unordered_map<int, Asset*> m_LoadedAssets;
        int m_IDCounter = 0;
    };
}
