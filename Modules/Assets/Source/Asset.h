#pragma once
#include "AssetsExports.h"

namespace Forgex::Assets
{
    class ASSETS_API Asset
    {
    public:
        virtual ~Asset() = default;

        virtual void Load(const char* assetPath) = 0;
        virtual void Save(const char* assetPath) = 0;
    };
}
