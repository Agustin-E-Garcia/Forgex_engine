#include "TextureAsset.h"
#include "../Utils/TextureLoader.h"

#include <ForgexFiles.h>

namespace Forgex::Graphics
{
    bool TextureAsset::Load()
    {
        LOG_CORE(Debug::LogLevel::Trace, "Loading TextureAsset: '{0}'", m_Path);

        nlohmann::json data;
        std::string errorString;
        if(!Files::ReadFile(m_Path.c_str(), data, errorString))
        {
            LOG_CORE(Debug::Error, "Failed to load TextureAsset '{0}': {1}", m_Path, errorString);
            return false;
        }

        m_Type = data["type"] == "cubemap" ? TextureType::Cubemap : TextureType::Default;

        Files::TextureData texture;
        if(m_Type == TextureType::Default)
        {
            m_TextureID = Utils::TextureLoader::LoadTexture(data["texture"], texture);
            m_GPUSize = texture.m_Width * texture.m_Height * texture.m_Channels;
        }
        else
        {
            std::vector<std::string> paths = data["textures"];
            m_TextureID = Utils::TextureLoader::LoadTexture(paths, texture);
            m_GPUSize = texture.m_Width * texture.m_Height * texture.m_Channels * 6;
        }

        return m_TextureID != -1;
    }

    void TextureAsset::Unload() { Graphics::Utils::TextureLoader::UnloadTexture(m_TextureID); }
}
