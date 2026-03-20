#pragma once
#include <fstream>
#include <string>
#include <ForgexAssets.h>
#include <ForgexDebugTools.h>

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

            std::ifstream file(m_Path);
            if(!file.is_open())
            {
                LOG_CORE(Debug::Error, "Failed to open ShaderAsset file: {0}", m_Path);
                return false;
            }

            std::string line;
            std::getline(file, line);

            size_t commaPos = line.find(',');
            if(commaPos == std::string::npos)
            {
                LOG_CORE(Debug::Error, "Invalid ShaderAsset format in '{0}': expected 'vertex,fragment'", m_Path);
                return false;
            }

            std::string vertexShader = line.substr(0, commaPos);
            std::string fragmentShader = line.substr(commaPos + 1);

            m_ShaderID = Utils::ShaderLoader::LoadShader(vertexShader.c_str(), fragmentShader.c_str());

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
