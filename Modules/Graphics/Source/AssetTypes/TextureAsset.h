#pragma once
#include "../Utils/TextureLoader.h"

#include <ForgexCore.h>
#include <ForgexAssets.h>

namespace Forgex::Graphics
{
    class TextureAsset : public Assets::Asset
    {
    public:
        bool Load() override
        {
            LOG_CORE(Debug::LogLevel::Info, "Loading TextureAsset: '{0}'", m_Path);
            m_TextureID = Utils::TextureLoader::LoadDefaultTexture(Graphics::Utils::TextureType::Default, m_Path.c_str());

            return m_TextureID != -1;
        }

        void Unload() override { Graphics::Utils::TextureLoader::UnloadTexture(m_TextureID); }

        bool Save(const std::string& assetPath) override
        {
            LOG_CORE(Debug::LogLevel::Info, "Saving TextureAsset: '{0}'", assetPath);
            return true;
        }

        int GetTextureID() { return m_TextureID; }
        size_t GetMemorySize() const override { return sizeof(*this); }

    private:
        int m_TextureID = -1;
    };
}
