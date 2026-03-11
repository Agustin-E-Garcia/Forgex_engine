#pragma once
#include <ForgexAssets.h>
#include <ForgexGraphics.h>
#include <ForgexDebugTools.h>

namespace Forgex::Core
{
    class TextureAsset : public Assets::Asset
    {
    public:
        void Load(const char* assetPath) override
        {
            LOG_CORE(Debug::LogLevel::Info, "Loading TextureAsset: '{0}'", assetPath);
            m_TextureID = Graphics::Utils::TextureLoader::LoadDefaultTexture(Graphics::Utils::TextureType::Default, assetPath);
        }

        void Save(const char* assetPath) override
        {
            LOG_CORE(Debug::LogLevel::Info, "Saving TextureAsset: '{0}'", assetPath);
        }

        int GetTextureID() { return m_TextureID; }

    private:
        int m_TextureID = -1;
    };
}
