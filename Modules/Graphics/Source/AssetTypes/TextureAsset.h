#pragma once
#include <ForgexCore.h>
#include <ForgexAssets.h>
#include <ForgexFiles.h>
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
        TextureAsset(std::string assetPath) : Assets::Asset(assetPath), m_TextureID(-1) {}

        bool Load() override
        {
            LOG_CORE(Debug::LogLevel::Info, "Loading TextureAsset: '{0}'", m_Path);

            nlohmann::json data;
            std::string errorString;
            if(!Files::ReadFile(m_Path.c_str(), data, errorString))
            {
                LOG_CORE(Debug::Error, "Failed to load TextureAsset '{0}': {1}", m_Path, errorString);
                return false;
            }

            m_Type = data["type"] == "cubemap" ? TextureType::Cubemap : TextureType::Default;

            if(m_Type == TextureType::Default)
            {
                m_TextureID = Utils::TextureLoader::LoadTexture(data["texture"], m_Data);
                m_GPUSize = m_Data.m_Width * m_Data.m_Height * m_Data.m_Channels;
            }
            else
            {
                std::vector<std::string> paths = data["textures"];
                m_TextureID = Utils::TextureLoader::LoadTexture(paths, m_Data);
                m_GPUSize = m_Data.m_Width * m_Data.m_Height * m_Data.m_Channels * 6;
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
        size_t GetCPUMemorySize() const override { return sizeof(*this); }

    private:
        int m_TextureID = -1;
        TextureType m_Type;

        Files::TextureData m_Data;
    };
}
