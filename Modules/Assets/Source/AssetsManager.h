#pragma once
#include "AssetsExports.h"
#include "Asset.h"
#include <unordered_map>

namespace Forgex::Assets
{
    class ASSETS_API AssetsManager
    {
    public:
        AssetsManager();
        ~AssetsManager();

        template<class T>
        T* LoadAsset(const char* assetPath)
        {
            static_assert(std::is_base_of<Asset, T>::value, "T must inherit from Asset");

            if(m_LoadedAssets.contains(assetPath)) return dynamic_cast<T*>(m_LoadedAssets[assetPath]);

            Asset* newAsset = new T();
            newAsset->Load(assetPath);
            m_LoadedAssets[assetPath] = newAsset;

            return static_cast<T*>(newAsset);
        }

        void UnloadAsset(const char* path)
        {
            if(!m_LoadedAssets.contains(path)) return;

            delete m_LoadedAssets[path];
            m_LoadedAssets.erase(path);
        }

    private:
        std::unordered_map<const char*, Asset*> m_LoadedAssets;
    };
}
