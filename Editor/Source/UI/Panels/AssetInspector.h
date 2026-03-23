#pragma once
#include "../GUIWindow.h"
#include <ForgexCore.h>
#include <ForgexAssets.h>

namespace Forgex::Editor::UI::Panels
{
    class AssetManagerInspectorPanel : public GUIWindow
    {
    public:
        AssetManagerInspectorPanel() : GUIWindow("Asset Inspector", false) {}
        ~AssetManagerInspectorPanel() {}

    protected:
        void OnDraw() override
        {
            const auto& assets = GET_SERVICE(Assets::AssetManager)->GetLoadedAssets();

            ImGui::Text("Loaded assets: %zu", assets.size());
            ImGui::Separator();

            if (ImGui::BeginTable("assets", 3, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY))
            {
                ImGui::TableSetupScrollFreeze(0, 1);
                ImGui::TableSetupColumn("Path", ImGuiTableColumnFlags_WidthStretch);
                ImGui::TableSetupColumn("Size (bytes)", ImGuiTableColumnFlags_WidthFixed, 100.0f);
                ImGui::TableSetupColumn("RefCount", ImGuiTableColumnFlags_WidthFixed, 100.0f);
                ImGui::TableHeadersRow();

                for (const auto& [id, asset] : assets)
                {
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0);
                    ImGui::TextUnformatted(asset->GetPath().c_str());
                    ImGui::TableSetColumnIndex(1);
                    ImGui::Text("%zu", asset->GetMemorySize());
                    ImGui::TableSetColumnIndex(2);
                    ImGui::Text("%i", asset->GetRefCount());
                }

                ImGui::EndTable();
            }
        }
    };
}
