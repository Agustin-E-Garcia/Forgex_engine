#pragma once
#include "AssetsManager.h"
#include <ForgexDebugTools.h>

namespace Forgex::Assets
{
    template<class T>
    class ASSETS_API AssetHandle
    {
    public:
        AssetHandle() : m_AssetID(-1) {}
        AssetHandle(int id) : m_AssetID(id) { InitializeHandle(); }
        AssetHandle(const AssetHandle& other) : m_AssetID(other.m_AssetID) { InitializeHandle(); }
        AssetHandle(AssetHandle&& other) noexcept : m_AssetID(other.m_AssetID) { other.m_AssetID = -1; }

        AssetHandle& operator=(AssetHandle&& other) noexcept
        {
            if(this == &other) return *this;

            DeInitializeHandle();

            m_AssetID = other.m_AssetID;
            other.m_AssetID = -1;
            return *this;
        }

        AssetHandle& operator=(const AssetHandle&) = delete;

        ~AssetHandle() { DeInitializeHandle(); }

        T* Get() const { return static_cast<T*>(AssetManager::Get().GetAsset(m_AssetID)); }
        T* operator->() const { return Get(); }
        T& operator*() const { return *Get(); }

        bool IsValid() { return AssetManager::Get().IsIDValid(m_AssetID); }

    private:
        int m_AssetID = -1;

        void InitializeHandle()
        {
            if(!IsValid()) return;
            AssetManager::Get().GetAsset(m_AssetID)->AddRefCount();
        }

        void DeInitializeHandle()
        {
            if(!IsValid()) return;
            if(AssetManager::Get().GetAsset(m_AssetID)->DecreaseRefCount()) AssetManager::Get().UnloadAsset(m_AssetID);
        }
    };
}
