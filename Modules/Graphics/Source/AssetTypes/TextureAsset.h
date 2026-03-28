#pragma once
#include <ForgexAssets.h>
#include <string>

namespace Forgex::Graphics
{
    enum TextureType
    {
        Default = 0,
        Cubemap = 1
    };

    class TextureAsset : public Assets::Asset
    {
    public:
        TextureAsset(std::string assetPath) : Assets::Asset(assetPath), m_TextureID(-1) {}

        bool Load() override;
        void Unload() override;
        bool Save(const std::string& assetPath) override { return false; }
        size_t GetCPUMemorySize() const override { return sizeof(*this); }

        int GetTextureID() { return m_TextureID; }

    private:
        int m_TextureID = -1;
        TextureType m_Type;
    };
}
