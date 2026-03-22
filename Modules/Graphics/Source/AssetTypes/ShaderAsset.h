#pragma once
#include <string>
#include <ForgexAssets.h>
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

            std::vector<std::string> shaderPaths;
            if(!Assets::Files::ReadFile(m_Path.c_str(), shaderPaths))
            {
                LOG_CORE(Debug::Error, "Invalid ShaderAsset format in '{0}': expected 'vertex,fragment'", m_Path);
                return false;
            }

            m_ShaderID = Utils::ShaderLoader::LoadShader(shaderPaths[0].c_str(), shaderPaths[1].c_str());

            return m_ShaderID != -1;
        }

        void Unload() override { Graphics::Utils::ShaderLoader::UnloadShader(m_ShaderID); }

        bool Save(const std::string& assetPath) override
        {
            LOG_CORE(Debug::LogLevel::Info, "Saving ShaderAsset: '{0}'", assetPath);
            return true;
        }

        int GetShaderID() { return m_ShaderID; }
        size_t GetMemorySize() const override { return sizeof(*this); }

    private:
        int m_ShaderID = -1;
    };
}
