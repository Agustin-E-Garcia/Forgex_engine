#pragma once
#include "../AssetsManager.h"

namespace Forgex::Assets
{
    template<class T>
    class AssetHandle
    {
    public:
        AssetHandle() : m_AssetID(-1), m_Manager(nullptr) {}
        AssetHandle(AssetManager* manager, int id) : m_AssetID(id), m_Manager(manager) { InitializeHandle(); }
        AssetHandle(const AssetHandle& other) : m_AssetID(other.m_AssetID), m_Manager(other.m_Manager) { InitializeHandle(); }
        AssetHandle(AssetHandle&& other) noexcept : m_AssetID(other.m_AssetID), m_Manager(other.m_Manager) { other.m_AssetID = -1; other.m_Manager = nullptr; }

        AssetHandle& operator=(AssetHandle&& other) noexcept
        {
            if(this == &other) return *this;

            DeInitializeHandle();

            m_AssetID = other.m_AssetID;
            m_Manager = other.m_Manager;
            other.m_AssetID = -1;
            other.m_Manager = nullptr;
            return *this;
        }

        AssetHandle& operator=(const AssetHandle&) = delete;

        ~AssetHandle() { DeInitializeHandle(); }

        T* Get() const { return m_Manager ? static_cast<T*>(m_Manager->GetAsset(m_AssetID)) : nullptr; }
        T* operator->() const { return Get(); }
        T& operator*() const { return *Get(); }

        bool IsValid() const
        {
            if(!m_Manager) return false;
            return m_Manager->IsIDValid(m_AssetID); 
        }

    private:
        int m_AssetID = -1;
        AssetManager* m_Manager;

        void InitializeHandle()
        {
            if(!m_Manager) return;
            if(!IsValid()) return;
            m_Manager->GetAsset(m_AssetID)->AddRefCount();
        }

        void DeInitializeHandle()
        {
            if(!m_Manager) return;
            if(!IsValid()) return;
            if(m_Manager->GetAsset(m_AssetID)->DecreaseRefCount()) m_Manager->UnloadAsset(m_AssetID);
        }
    };
}
