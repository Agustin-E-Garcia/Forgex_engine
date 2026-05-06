#pragma once
#include "../GraphicsExports.h"
#include <string>
#include <ForgexAssets.h>

namespace Forgex::Graphics
{
    class GRAPHICS_API ShaderAsset : public Assets::Asset
    {
    public:
        ShaderAsset(std::string assetPath) : Assets::Asset(assetPath) {}

        bool Load() override;
        void Unload() override;
        bool Save(const std::string& assetPath) override { return false; }
        size_t GetCPUMemorySize() const override { return sizeof(*this); }

        int GetShaderID() { return m_ShaderID; }

    private:
        int m_ShaderID = -1;
    };
}
