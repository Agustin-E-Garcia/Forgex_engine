#pragma once
#include "../GUIWindow.h"
#include "imgui.h"
#include <ForgexDebugTools.h>
#include <string>
#include <vector>

namespace Forgex::UI
{
    class ConsolePanel : public GUIWindow
    {
    public:
        ConsolePanel() : GUIWindow("Console", false) {}
        ~ConsolePanel() {}

    protected:
        void OnDraw() override
        {
            // --- Toolbar ---
            if (ImGui::Button("Clear")) ClearLog();
            ImGui::SameLine();

            if (ImGui::BeginPopup("Options"))
            {
                ImGui::Checkbox("Auto-Scroll", &m_AutoScroll);
                ImGui::Separator();
                ImGui::Text("Severity");
                ImGui::Checkbox("Trace",    &m_ShowLevel[Debug::Trace]);
                ImGui::Checkbox("Info",     &m_ShowLevel[Debug::Info]);
                ImGui::Checkbox("Warning",  &m_ShowLevel[Debug::Warning]);
                ImGui::Checkbox("Error",    &m_ShowLevel[Debug::Error]);
                ImGui::Checkbox("Critical", &m_ShowLevel[Debug::Critical]);
                ImGui::EndPopup();
            }

            ImGui::SetNextItemShortcut(ImGuiMod_Ctrl | ImGuiKey_O, ImGuiInputFlags_Tooltip);
            if (ImGui::Button("Options"))
                ImGui::OpenPopup("Options");

            ImGui::SameLine();
            m_Filter.Draw("Filter", -1.0f);
            ImGui::Separator();

            // --- Scrolling log area ---
            ImGuiStyle& style = ImGui::GetStyle();
            const float footer_height = style.DockingSeparatorSize + style.ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
            if (ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height), ImGuiChildFlags_NavFlattened, ImGuiWindowFlags_HorizontalScrollbar))
            {
                if (ImGui::BeginPopupContextWindow())
                {
                    if (ImGui::Selectable("Clear")) ClearLog();
                    ImGui::EndPopup();
                }

                ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1));

                for (int i = 0; i < (int)m_Logs.size(); i++)
                {
                    const auto& entry = m_Logs[i];

                    if (!m_ShowLevel[entry.level]) continue;
                    if (!m_Filter.PassFilter(entry.text.c_str())) continue;

                    ImGui::TextColored(LevelColor(entry.level), "%s", entry.text.c_str());

                    if (ImGui::BeginPopupContextItem(("log_ctx_" + std::to_string(i)).c_str()))
                    {
                        if (ImGui::MenuItem("Copy"))
                            ImGui::SetClipboardText(entry.text.c_str());
                        ImGui::EndPopup();
                    }
                }

                if (m_AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
                    ImGui::SetScrollHereY(1.0f);

                ImGui::PopStyleVar();
            }
            ImGui::EndChild();
            ImGui::Separator();

            // --- Command input ---
            bool reclaim_focus = false;
            ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_EscapeClearsAll;
            if (ImGui::InputText("Input", m_CommandBuffer, IM_COUNTOF(m_CommandBuffer), input_text_flags))
            {
                if(m_CommandBuffer[0] != '\0')
                {
                    Debug::Command::Get().Execute(std::string(m_CommandBuffer));
                    m_CommandBuffer[0] = '\0';
                }

                reclaim_focus = true;
            }

            ImGui::SetItemDefaultFocus();
            if (reclaim_focus)
                ImGui::SetKeyboardFocusHere(-1);
        }

        void OnUpdate() override
        {
            while (Debug::Log::HasConsoleMessage())
            {
                auto msg = Debug::Log::GetNextConsoleMessage();
                m_Logs.push_back({ msg.text, msg.level });
            }
        }

    private:
        struct LogEntry
        {
            std::string text;
            Debug::LogLevel level;
        };

        char m_CommandBuffer[256] = {};
        bool m_AutoScroll = true;
        bool m_ShowLevel[5] = { true, true, true, true, true };
        ImGuiTextFilter m_Filter;
        std::vector<LogEntry> m_Logs;

        void ClearLog() { m_Logs.clear(); }

        static ImVec4 LevelColor(Debug::LogLevel level)
        {
            switch (level)
            {
                case Debug::Trace:    return ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
                case Debug::Info:     return ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
                case Debug::Warning:  return ImVec4(1.0f, 0.8f, 0.0f, 1.0f);
                case Debug::Error:    return ImVec4(1.0f, 0.4f, 0.4f, 1.0f);
                case Debug::Critical: return ImVec4(1.0f, 0.2f, 0.6f, 1.0f);
                default:              return ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
            }
        }
    };
}
