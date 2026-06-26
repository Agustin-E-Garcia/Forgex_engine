#pragma once
#include "../GUIWindow.h"
#include <ForgexCore.h>
#include <algorithm>
#include <string>
#include <vector>

namespace Forgex::Editor::UI::Panels
{
    class ProfilerPanel : public GUIWindow
    {
    public:
        ProfilerPanel() : GUIWindow("Profiler", false) {}
        ~ProfilerPanel() {}

    protected:
        float MedianMs(const Debug::ProfileResult& result) const
        {
            const size_t count = result.m_Buffer.Size();
            if (count == 0) return 0.0f;

            std::vector<long long> samples;
            samples.reserve(count);
            for (size_t i = 0; i < count; ++i)
                samples.push_back(result.m_Buffer.Get(i));

            std::sort(samples.begin(), samples.end());

            const size_t mid = count / 2;
            if (count % 2 == 0)
                return (samples[mid - 1] + samples[mid]) / 2.0f;

            return (float)samples[mid];
        }

        void OnDraw() override
        {
            const auto& results = GET_SERVICE(Debug::DebugManager)->GetProfiler()->GetResults();

            ImGui::Text("Samples: %zu", results.size());
            ImGui::SameLine();
            if (ImGui::Button("Clear"))
                GET_SERVICE(Debug::DebugManager)->GetProfiler()->Clear();

            ImGui::Separator();

            // Sort by path so scopes come out in depth-first (parent before children) order.
            std::vector<const Debug::ProfileResult*> ordered;
            ordered.reserve(results.size());
            for (const auto& [path, result] : results)
                ordered.push_back(&result);

            std::sort(ordered.begin(), ordered.end(),
                [](const Debug::ProfileResult* a, const Debug::ProfileResult* b) { return a->m_Path < b->m_Path; });

            if (ImGui::BeginTable("profiler", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY))
            {
                ImGui::TableSetupScrollFreeze(0, 1);
                ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthStretch);
                ImGui::TableSetupColumn("Duration (ms)", ImGuiTableColumnFlags_WidthFixed, 110.0f);
                ImGui::TableHeadersRow();

                int pushedDepth = 0;     // tree levels currently pushed onto the ImGui stack
                int collapsedDepth = -1; // depth of a collapsed node; deeper entries are skipped

                const size_t total = ordered.size();
                for (size_t i = 0; i < total; ++i)
                {
                    const Debug::ProfileResult* result = ordered[i];
                    const int depth = result->m_Depth;

                    // Inside a collapsed branch: skip every entry deeper than where it collapsed.
                    if (collapsedDepth != -1 && depth > collapsedDepth)
                        continue;
                    collapsedDepth = -1;

                    // Close any open levels until this entry's parent is the deepest open one.
                    while (pushedDepth >= depth)
                    {
                        ImGui::TreePop();
                        pushedDepth--;
                    }

                    // A node is a leaf when the next entry isn't one of its children (deeper).
                    const bool isLeaf = (i + 1 >= total) || (ordered[i + 1]->m_Depth <= depth);

                    const std::string& path = result->m_Path;
                    const size_t slash = path.find_last_of('/');
                    const char* name = (slash == std::string::npos) ? path.c_str() : path.c_str() + slash + 1;

                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0);

                    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTreeNodeFlags_DefaultOpen;
                    if (isLeaf)
                        flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;

                    // Use the full path as the ID so equally-named scopes never collide.
                    const bool open = ImGui::TreeNodeEx(path.c_str(), flags, "%s", name);

                    ImGui::TableSetColumnIndex(1);
                    ImGui::Text("%.4fms", MedianMs(*result));

                    if (!isLeaf)
                    {
                        if (open)
                            pushedDepth++;       // descend into this branch
                        else
                            collapsedDepth = depth; // collapsed: skip its descendants
                    }
                }

                // Close whatever is still open after the last entry.
                while (pushedDepth > 0)
                {
                    ImGui::TreePop();
                    pushedDepth--;
                }

                ImGui::EndTable();
            }
        }
    };
}
