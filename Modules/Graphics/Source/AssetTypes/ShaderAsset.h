#pragma once
#include <json.hpp>
#include <string>
#include <ForgexAssets.h>
#include <ForgexFiles.h>
#include <ForgexCore.h>

#include "../Utils/ShaderLoader.h"

namespace Forgex::Graphics
{
    class ShaderAsset : public Assets::Asset
    {
    public:
        ShaderAsset(std::string assetPath) : Assets::Asset(assetPath) {}

        bool Load() override
        {
            LOG_CORE(Debug::LogLevel::Info, "Loading ShaderAsset: '{0}'", m_Path);

            nlohmann::json data;
            std::string errorString;
            if(!Files::ReadFile(m_Path.c_str(), data, errorString))
            {
                LOG_CORE(Debug::Error, "Failed to load '{0}': {1}", m_Path, errorString);
                return false;
            }

            std::string vertex = data["Vertex"];
            std::string fragment = data["Fragment"];
            m_ShaderID = Utils::ShaderLoader::LoadShader(vertex.c_str(), fragment.c_str());

            return m_ShaderID != -1;
        }

        void Unload() override { Graphics::Utils::ShaderLoader::UnloadShader(m_ShaderID); }

        bool Save(const std::string& assetPath) override { return false; }

        int GetShaderID() { return m_ShaderID; }
        size_t GetCPUMemorySize() const override { return sizeof(*this); }

    private:
        int m_ShaderID = -1;
    };
}
