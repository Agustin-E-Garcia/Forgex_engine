#pragma once
#include "ShaderAsset.h"
#include "TextureAsset.h"
#include "glm/fwd.hpp"
#include <string>
#include <unordered_map>
#include <variant>

namespace Forgex::Graphics 
{
    using MaterialProperty = std::variant<float, int, bool, glm::vec3, glm::vec4, Assets::AssetHandle<TextureAsset>>;

    class MaterialAsset : public Assets::Asset
    {
    public:
        MaterialAsset(std::string assetPath) : Assets::Asset(assetPath) {}

        bool Load() override
        {
            LOG_CORE(Debug::Info, "Loading MaterialAsset {0}", m_Path);

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

                if      (type == "float")       m_Properties[name] = val.get<float>();
                else if (type == "int")         m_Properties[name] = val.get<int>();
                else if (type == "bool")        m_Properties[name] = val.get<bool>();
                else if (type == "vec3")        m_Properties[name] = glm::vec3(val[0], val[1], val[2]);
                else if (type == "vec4")        m_Properties[name] = glm::vec4(val[0], val[1], val[2], val[3]);
                else if (type == "texture")     m_Properties[name] = GET_SERVICE(Assets::AssetManager)->LoadAsset<TextureAsset>(val.get<std::string>());
            }

            return true;
        }

        bool Save(const std::string &assetPath) override { return false; }
        size_t GetCPUMemorySize() const override { return sizeof(*this); }

        int GetShaderID() { return m_ShaderAsset->GetShaderID(); }
        const std::unordered_map<std::string, MaterialProperty>& GetProperties() const { return m_Properties; }
        std::unordered_map<std::string, MaterialProperty>& GetProperties() { return m_Properties; }

    private:
        Assets::AssetHandle<ShaderAsset> m_ShaderAsset;
        std::unordered_map<std::string, MaterialProperty> m_Properties;
    };
}
