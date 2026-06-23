#pragma once
#include "../GraphicsExports.h"
#include <ForgexAssets.h>
#include <string>
#include <unordered_map>
#include <variant>
#include "TextureAsset.h"

namespace Forgex::Graphics
{
    class ShaderAsset;

    struct MaterialProperty
    {
        int m_Location;
        std::variant<float, int, bool, glm::vec2, glm::vec3, glm::vec4, Assets::AssetHandle<TextureAsset>> m_Property;
    };

    class GRAPHICS_API MaterialAsset : public Assets::Asset
    {
    public:
        MaterialAsset(std::string assetPath) : Assets::Asset(assetPath) {}

        bool Load() override;
        bool Save(const std::string &assetPath) override { return false; }
        size_t GetCPUMemorySize() const override { return sizeof(*this); }

        int GetShaderID();
        void SetupProperties();

        const int GetModelMatrixLocation() { return m_ModelMatrixLocation; }

        const std::unordered_map<std::string, MaterialProperty>& GetProperties() const { return m_Properties; }
        std::unordered_map<std::string, MaterialProperty>& GetProperties() { return m_Properties; }

        const std::unordered_map<std::string, MaterialProperty>& GetUniforms() const { return m_Uniforms; }
        std::unordered_map<std::string, MaterialProperty>& GetUniforms() { return m_Uniforms; }


    private:
        Assets::AssetHandle<ShaderAsset> m_ShaderAsset;
        int m_ModelMatrixLocation = -1;
        std::unordered_map<std::string, MaterialProperty> m_Properties;
        std::unordered_map<std::string, MaterialProperty> m_Uniforms;
    };
}
