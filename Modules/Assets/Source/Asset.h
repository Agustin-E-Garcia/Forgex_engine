#pragma once
#include "AssetsExports.h"
#include <string>

namespace Forgex::Assets
{

    class ASSETS_API Asset
    {
    public:
        Asset(std::string assetPath) : m_Path(assetPath) {}
        virtual ~Asset() { Unload(); }

        virtual bool Load() = 0;
        virtual void Unload() {}
        virtual bool Save(const std::string& assetPath) = 0;
        virtual size_t GetMemorySize() const { return sizeof(*this); }

        void AddRefCount() { m_RefCount += 1; }
        bool DecreaseRefCount() 
        {
            m_RefCount -= 1;
            return m_RefCount <= 0;
        }

        std::string GetPath() { return m_Path; }
        int GetRefCount() { return m_RefCount; }

    protected:
        std::string m_Path = "";

    private:
        int m_RefCount = 0;
    };
}
