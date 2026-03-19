#pragma once
#include "AssetsExports.h"
#include <string>

namespace Forgex::Assets
{
    class ASSETS_API Asset
    {
    public:
        virtual ~Asset() { Unload(); }

        virtual bool Load(const std::string& assetPath) = 0;
        virtual void Unload() {}
        virtual bool Save(const std::string& assetPath) = 0;
        virtual size_t GetMemorySize() const { return sizeof(*this); }
    };
}
