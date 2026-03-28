#include "ShaderAsset.h"
#include "../Utils/ShaderLoader.h"

#include <ForgexFiles.h>

namespace Forgex::Graphics
{
    bool ShaderAsset::Load()
    {
        LOG_CORE(Debug::LogLevel::Trace, "Loading ShaderAsset: '{0}'", m_Path);

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

    void ShaderAsset::Unload() { Graphics::Utils::ShaderLoader::UnloadShader(m_ShaderID); }
}
