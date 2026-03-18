#pragma once
#include "AssetsExports.h"
#include <string>

namespace Forgex::Assets
{
    class ASSETS_API Asset
    {
    public:
        virtual ~Asset() = default;

        virtual bool Load(const std::string& assetPath) = 0;
        virtual bool Save(const std::string& assetPath) = 0;
    };
}
