#pragma once
#include <ForgexCore.h>
#include <ForgexAssets.h>
#include <string>

#include "../Utils/TextureLoader.h"

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
        TextureAsset(std::string assetPath, TextureType type) : Assets::Asset(assetPath), m_Type(type), m_TextureID(-1) {}

        bool Load() override
        {
            LOG_CORE(Debug::LogLevel::Info, "Loading TextureAsset: '{0}'", m_Path);

            // if textureType is cubemap, we need to parse the texture file into an array of texture files (comma separated for now) and call the correct function
            if(m_Type == TextureType::Default)
            {
                m_TextureID = Utils::TextureLoader::LoadTexture(m_Path.c_str());
            }
            else
            {
                std::vector<std::string> texturePaths;
                if(!Assets::Files::ReadFile(m_Path.c_str(), texturePaths))
                {
                    LOG_CORE(Debug::Error, "Invalid TextureAsset of type Cubemap in '{0}': expected texture paths with comma-separated-values", m_Path);
                    return false;
                }
                m_TextureID = Utils::TextureLoader::LoadTexture(texturePaths);
            }


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
        TextureType m_Type;
    };
}
