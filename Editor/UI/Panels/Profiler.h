#pragma once
#include "../GUIWindow.h"
#include <ForgexDebugTools.h>
#include "imgui.h"

namespace Forgex::UI
{
    class Profiler : public GUIWindow
    {
    public:
        Profiler() : GUIWindow("Profiler", false) {}
        ~Profiler() {}

    protected:
        void OnDraw() override
        {
            const auto& results = Debug::Profiler::Get().GetResults();

            ImGui::Text("Samples: %zu", results.size());
            ImGui::SameLine();
            if (ImGui::Button("Clear"))
                Debug::Profiler::Get().Clear();

            ImGui::Separator();

            if (ImGui::BeginTable("profiler", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY))
            {
                ImGui::TableSetupScrollFreeze(0, 1);
                ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthStretch);
                ImGui::TableSetupColumn("Duration (ms)", ImGuiTableColumnFlags_WidthFixed, 110.0f);
                ImGui::TableHeadersRow();

                for (const auto& [name, result] : results)
                {
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0);
                    ImGui::TextUnformatted(name.c_str());
                    ImGui::TableSetColumnIndex(1);
                    ImGui::Text("%.4fms", result.m_Duration / (float)result.m_Samples);
                }

                ImGui::EndTable();
            }
        }
    };
}
