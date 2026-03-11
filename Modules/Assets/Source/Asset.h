#pragma once
#include "AssetsExports.h"

namespace Forgex::Assets
{
    class ASSETS_API Asset
    {
    public:
        virtual ~Asset() = default;

        virtual bool Load(const char* assetPath) = 0;
        virtual bool Save(const char* assetPath) = 0;
    };
}
