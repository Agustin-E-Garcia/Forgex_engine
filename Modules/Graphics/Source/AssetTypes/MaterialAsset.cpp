#include "MaterialAsset.h"
#include "ShaderAsset.h"

#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <type_traits>
#include <GL/glew.h>
#include <variant>

#include <ForgexFiles.h>

namespace Forgex::Graphics
{
    bool MaterialAsset::Load()
    {
        LOG_CORE(Debug::Trace, "Loading MaterialAsset {0}", m_Path);

        nlohmann::json data;
        std::string errorString;
        if(!Files::ReadFile(m_Path.c_str(), data, errorString))
        {
            LOG_CORE(Debug::Error, "Failed to load '{0}': {1}", m_Path, errorString);
            return false;
        }

        m_ShaderAsset = GET_SERVICE(Assets::AssetManager)->LoadAsset<ShaderAsset>(data["shader"]);

        for(auto& [name, entry] : data["properties"].items())
        {
            const std::string& type = entry["type"];
            const auto& val = entry["value"];

            std::string fullName("material." + name);
            int location = glGetUniformLocation(m_ShaderAsset->GetShaderID(), fullName.c_str());
            std::variant<float, int, bool, glm::vec3, glm::vec4, Assets::AssetHandle<TextureAsset>> property;

            if      (type == "float")       property = val.get<float>();
            else if (type == "int")         property = val.get<int>();
            else if (type == "bool")        property = val.get<bool>();
            else if (type == "vec3")        property = glm::vec3(val[0], val[1], val[2]);
            else if (type == "vec4")        property = glm::vec4(val[0], val[1], val[2], val[3]);
            else if (type == "texture")
            {
                if(val.get<std::string>().empty())
                {
                    property = Assets::AssetHandle<TextureAsset>{};
                }
                else property = GET_SERVICE(Assets::AssetManager)->LoadAsset<TextureAsset>(val.get<std::string>());
            }

            m_Properties[name] = { location, property };
        }
        return true;
    }

    int MaterialAsset::GetShaderID() { return m_ShaderAsset->GetShaderID(); }

    void MaterialAsset::SetupProperties()
    {
        for(const auto& [name, value] : m_Properties)
        {
            int loc = value.m_Location;
            if(loc == -1)
            {
                LOG_CORE(Debug::Error, "Unable to find loc '{0}'", name);
            }

            std::visit([&](auto&& v)
            {
                using T = std::decay_t<decltype(v)>;
                if      constexpr (std::is_same_v<T, float>)     glUniform1f(loc, v);
                else if constexpr (std::is_same_v<T, int>)       glUniform1i(loc, v);
                else if constexpr (std::is_same_v<T, bool>)      glUniform1i(loc, (int)v);
                else if constexpr (std::is_same_v<T, glm::vec3>) glUniform3fv(loc, 1, glm::value_ptr(v));
                else if constexpr (std::is_same_v<T, glm::vec4>) glUniform4fv(loc, 1, glm::value_ptr(v));
                else if constexpr (std::is_same_v<T, Assets::AssetHandle<TextureAsset>>)
                {
                    int textureID = v.IsValid() ? v->GetTextureID() : TextureAsset::GetDefaultWhiteTextureID();
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, textureID);
                    glUniform1i(loc, 0);
                }
            }, value.m_Property);
        }
    }
}
