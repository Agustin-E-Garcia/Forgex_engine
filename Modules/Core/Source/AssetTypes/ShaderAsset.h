#pragma once
#include <fstream>
#include <string>
#include <ForgexAssets.h>
#include <ForgexGraphics.h>
#include <ForgexDebugTools.h>

namespace Forgex::Core
{
    class ShaderAsset : public Assets::Asset
    {
    public:
        bool Load(const char* assetPath) override
        {
            LOG_CORE(Debug::LogLevel::Info, "Loading ShaderAsset: '{0}'", assetPath);

            std::ifstream file(assetPath);
            std::string line;
            std::getline(file, line);

            size_t commaPos = line.find(',');
            std::string vertexShader = line.substr(0, commaPos);
            std::string fragmentShader = line.substr(commaPos + 1);

            m_ShaderID = Graphics::Utils::ShaderLoader::LoadShader(vertexShader.c_str(), fragmentShader.c_str());

            return m_ShaderID != -1;
        }

        bool Save(const char* assetPath) override
        {
            LOG_CORE(Debug::LogLevel::Info, "Saving ShaderAsset: '{0}'", assetPath);
            return true;
        }

        int GetShaderID() { return m_ShaderID; }

    private:
        int m_ShaderID = -1;
    };
}
