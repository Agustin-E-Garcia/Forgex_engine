#pragma once
#include <string>

namespace Forgex::Assets
{
    class Asset
    {
    public:
        Asset(std::string assetPath, bool isRuntime = false) : m_Path(assetPath), m_IsRuntime(isRuntime) {}
        virtual ~Asset() { Unload(); }

        virtual bool Load() = 0;
        virtual void Unload() {}
        virtual bool Save(const std::string& assetPath) = 0;
        virtual size_t GetCPUMemorySize() const { return sizeof(*this); }
        virtual size_t GetGPUMemorySize() const { return m_GPUSize; }

        void AddRefCount() { m_RefCount += 1; }
        bool DecreaseRefCount() 
        {
            m_RefCount -= 1;
            return m_RefCount <= 0;
        }

        std::string GetPath() const { return m_Path; }
        int GetRefCount() const { return m_RefCount; }
        bool IsRuntimeAsset() const { return m_IsRuntime; }

    protected:
        std::string m_Path = "";
        size_t m_GPUSize = 0;

    private:
        int m_RefCount = 0;
        bool m_IsRuntime = false;
    };
}
