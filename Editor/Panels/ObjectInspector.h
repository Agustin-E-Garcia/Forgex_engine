#pragma once

#include "SceneViewer.h"
#include "imgui.h"
#include <string>
#include <ForgexDebugTools.h>

namespace Forgex::UI::Panels
{
    class ObjectInspector : public GUIWindow
    {
    public:
        ObjectInspector(SceneViewer* sceneViewer) : GUIWindow("Object Inspector", true), m_SceneViewer(sceneViewer) {}
        ~ObjectInspector() {}
    protected:
        void OnDraw() override
        {
            if(!m_SceneViewer->HasObjectSelected()) return;

            Core::ObjectEntry obj = m_SceneViewer->GetSelectedObject();
            ImGui::Text(obj.m_ObjectName.c_str());

            for (Core::ComponentData component : obj.m_ComponentData) 
            {
                 ImGui::SeparatorText(component.m_Name.c_str());
                 for (Core::VariableData variable : component.m_Variables)
                 {
                    ImGui::Text(variable.m_Name.c_str());
                    switch (variable.m_Type) 
                    {
                        case Core::Vector3:
                            ImGui::InputFloat3(variable.m_Name.c_str(), (float*)variable.m_Ptr);
                            break;
                        case Core::Bool:
                            ImGui::Checkbox(variable.m_Name.c_str(), (bool*)variable.m_Ptr);
                            break;
                        case Core::Float:
                            ImGui::SliderFloat(variable.m_Name.c_str(), (float*)variable.m_Ptr, 70.0f, 100.0f);
                            break;
                        default:
                            break;
                    }
                 }
           }
            ImGui::Separator();
        }

        void Update() override {}
    private:
        SceneViewer* m_SceneViewer = nullptr;
    };
}
