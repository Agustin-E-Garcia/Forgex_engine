#pragma once
#include <ForgexAssets.h>
#include <ForgexGraphics.h>
#include <ForgexDebugTools.h>

namespace Forgex::Core
{
    class TextureAsset : public Assets::Asset
    {
    public:
        bool Load(const std::string& assetPath) override
        {
            LOG_CORE(Debug::LogLevel::Info, "Loading TextureAsset: '{0}'", assetPath);
            m_TextureID = Graphics::Utils::TextureLoader::LoadDefaultTexture(Graphics::Utils::TextureType::Default, assetPath.c_str());

            return m_TextureID != -1;
        }

        bool Save(const std::string& assetPath) override
        {
            LOG_CORE(Debug::LogLevel::Info, "Saving TextureAsset: '{0}'", assetPath);
            return true;
        }

        int GetTextureID() { return m_TextureID; }

    private:
        int m_TextureID = -1;
    };
}
