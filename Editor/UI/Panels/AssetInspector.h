#pragma once
#include "../GUIWindow.h"
#include <ForgexAssets.h>
#include "imgui.h"

namespace Forgex::UI
{
    class AssetInspector : public GUIWindow
    {
    public:
        AssetInspector() : GUIWindow("Asset Inspector", false) {}
        ~AssetInspector() {}

    protected:
        void OnDraw() override
        {
            const auto& assets = Assets::AssetManager::Get().GetLoadedAssets();

            ImGui::Text("Loaded assets: %zu", assets.size());
            ImGui::Separator();

            if (ImGui::BeginTable("assets", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY))
            {
                ImGui::TableSetupScrollFreeze(0, 1);
                ImGui::TableSetupColumn("Path", ImGuiTableColumnFlags_WidthStretch);
                ImGui::TableSetupColumn("Size (bytes)", ImGuiTableColumnFlags_WidthFixed, 100.0f);
                ImGui::TableHeadersRow();

                for (const auto& [path, asset] : assets)
                {
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0);
                    ImGui::TextUnformatted(path.c_str());
                    ImGui::TableSetColumnIndex(1);
                    ImGui::Text("%zu", asset->GetMemorySize());
                }

                ImGui::EndTable();
            }
        }
    };
}
