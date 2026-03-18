#pragma once
#include "AssetsExports.h"
#include "Asset.h"
#include <unordered_map>
#include <string>

namespace Forgex::Assets
{
    class ASSETS_API AssetManager
    {
    public:
        static AssetManager& Get()
        {
            static AssetManager instance;
            return instance;
        }

        template<class T>
        T* LoadAsset(const std::string& assetPath)
        {
            static_assert(std::is_base_of<Asset, T>::value, "T must inherit from Asset");

            if(m_LoadedAssets.contains(assetPath)) return dynamic_cast<T*>(m_LoadedAssets[assetPath]);

            Asset* newAsset = new T();
            if(!newAsset->Load(assetPath))
            {
                delete newAsset;
                return nullptr;
            }

            m_LoadedAssets[assetPath] = newAsset;

            return static_cast<T*>(newAsset);
        }

        void UnloadAsset(const std::string& path)
        {
            if(!m_LoadedAssets.contains(path)) return;

            delete m_LoadedAssets[path];
            m_LoadedAssets.erase(path);
        }

    private:
        AssetManager() = default;
        AssetManager(const AssetManager&) = delete;
        AssetManager& operator=(const AssetManager&) = delete;

        std::unordered_map<std::string, Asset*> m_LoadedAssets;
    };
}
