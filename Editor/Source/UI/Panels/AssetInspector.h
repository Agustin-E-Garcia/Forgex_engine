#pragma once
#include "../GUIWindow.h"
#include "../Utils/UIUtils.h"
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

            if (ImGui::BeginPopup("Options"))
            {
                ImGui::Text("Asset Types");
                ImGui::Checkbox("Runtime Assets",     &m_ShowRuntimeAssets);
                ImGui::Checkbox("Non-Runtime Assets", &m_ShowNonRuntimeAssets);
                ImGui::EndPopup();
            }

            ImGui::SetNextItemShortcut(ImGuiMod_Ctrl | ImGuiKey_O, ImGuiInputFlags_Tooltip);
            if (ImGui::Button("Options"))
                ImGui::OpenPopup("Options");

            ImGui::Separator();

            size_t totalCPU = 0, totalGPU = 0;

            float footerHeight = ImGui::GetFrameHeightWithSpacing();
            ImVec2 tableSize(0.0f, ImGui::GetContentRegionAvail().y - footerHeight);
            if (ImGui::BeginTable("assets", 4, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY, tableSize))
            {
                ImGui::TableSetupScrollFreeze(0, 1);
                ImGui::TableSetupColumn("Path", ImGuiTableColumnFlags_WidthStretch);
                ImGui::TableSetupColumn("CPU Size", ImGuiTableColumnFlags_WidthFixed, 120.0f);
                ImGui::TableSetupColumn("GPU Size", ImGuiTableColumnFlags_WidthFixed, 120.0f);
                ImGui::TableSetupColumn("RefCount", ImGuiTableColumnFlags_WidthFixed, 100.0f);
                ImGui::TableHeadersRow();

                for (const auto& [id, asset] : assets)
                {
                    totalCPU += asset->GetCPUMemorySize();
                    totalGPU += asset->GetGPUMemorySize();

                    if (asset->IsRuntimeAsset()  && !m_ShowRuntimeAssets)    continue;
                    if (!asset->IsRuntimeAsset() && !m_ShowNonRuntimeAssets) continue;

                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0);
                    ImGui::TextUnformatted(asset->GetPath().c_str());
                    ImGui::TableSetColumnIndex(1);
                    ImGui::TextUnformatted(Utils::FormatBytes(asset->GetCPUMemorySize()).c_str());
                    ImGui::TableSetColumnIndex(2);
                    ImGui::TextUnformatted(Utils::FormatBytes(asset->GetGPUMemorySize()).c_str());
                    ImGui::TableSetColumnIndex(3);
                    ImGui::Text("%i", asset->GetRefCount());
                }

                ImGui::EndTable();
            }

            ImGui::Separator();
            ImGui::Text("Loaded assets: %zu", assets.size());
            ImGui::SameLine();
            ImGui::Text("| CPU: %s", Utils::FormatBytes(totalCPU).c_str());
            ImGui::SameLine();
            ImGui::Text("| GPU: %s", Utils::FormatBytes(totalGPU).c_str());
        }

    private:
        bool m_ShowRuntimeAssets    = true;
        bool m_ShowNonRuntimeAssets = true;
    };
}
