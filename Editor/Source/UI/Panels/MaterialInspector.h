#pragma once
#include "../GUIWindow.h"
#include "imgui.h"
#include <ForgexCore.h>
#include <ForgexAssets.h>
#include <ForgexGraphics.h>
#include <glm/gtc/type_ptr.hpp>

namespace Forgex::Editor::UI::Panels
{
    class MaterialInspectorPanel : public GUIWindow
    {
    public:
        MaterialInspectorPanel() : GUIWindow("Material Inspector", false) {}
        ~MaterialInspectorPanel() {}

    protected:
        void OnDraw() override
        {
            auto materials = GET_SERVICE(Assets::AssetManager)->GetAssetsOfType<Graphics::MaterialAsset>();

            float listWidth = 200.0f;
            ImGui::BeginChild("##material_list", ImVec2(listWidth, 0.0f), true);

            ImGui::TextUnformatted("Materials");
            ImGui::Separator();

            for(int i = 0; i < static_cast<int>(materials.size()); i++)
            {
                Graphics::MaterialAsset* mat = materials[i];
                std::string label = mat->GetPath();
                size_t slash = label.find_last_of("/\\");
                if(slash != std::string::npos) label = label.substr(slash + 1);

                bool selected = (m_SelectedMaterial == mat);
                if(ImGui::Selectable(label.c_str(), selected))
                    m_SelectedMaterial = mat;
            }

            ImGui::EndChild();

            ImGui::SameLine();

            ImGui::BeginChild("##material_properties", ImVec2(0.0f, 0.0f), true);

            if(m_SelectedMaterial)
            {
                ImGui::Text("Material: %s", m_SelectedMaterial->GetPath().c_str());
                ImGui::Separator();

                auto& properties = m_SelectedMaterial->GetProperties();
                for(auto& [name, value] : properties)
                {
                    std::visit([&](auto& v)
                    {
                        using ValueType = std::decay_t<decltype(v)>;

                        if      constexpr (std::is_same_v<ValueType, float>)     ImGui::DragFloat(name.c_str(), &v, 0.01f);
                        else if constexpr (std::is_same_v<ValueType, int>)       ImGui::DragInt(name.c_str(), &v);
                        else if constexpr (std::is_same_v<ValueType, bool>)      ImGui::Checkbox(name.c_str(), &v);
                        else if constexpr (std::is_same_v<ValueType, glm::vec3>) ImGui::ColorEdit3(name.c_str(), glm::value_ptr(v));
                        else if constexpr (std::is_same_v<ValueType, glm::vec4>) ImGui::ColorEdit4(name.c_str(), glm::value_ptr(v));
                        else if constexpr (std::is_same_v<ValueType, Assets::AssetHandle<Graphics::TextureAsset>>)
                        {
                            ImGui::Text("%s", name.c_str());
                            Assets::AssetHandle<Graphics::TextureAsset> assetHandle = v;
                            if(assetHandle.IsValid() && assetHandle->GetTextureID() != -1)
                            {
                                //ImGui::Image((ImTextureID)(intptr_t)v->GetTextureID(), ImVec2(64, 64));
                                ImGui::Text("%s", assetHandle->GetPath().c_str());
                            }
                            else
                                ImGui::TextDisabled("(no texture)");
                        }
                    }, value.m_Property);
                }
            }
            else
            {
                ImGui::TextDisabled("Select a material to inspect");
            }

            ImGui::EndChild();
        }

    private:
        Graphics::MaterialAsset* m_SelectedMaterial = nullptr;
    };
}
