#pragma once
#include <Engine.h>

class SceneInspector : public Menu
{
public:
	SceneInspector() : Menu("Scene Inspector"), m_ActiveScene(nullptr) {}
	~SceneInspector() {}

	inline void SetActiveScene(Scene* activeScene) { m_ActiveScene = activeScene; }

protected:

	void OnDraw() override
	{
        DisplaySceneInspector();
        DisplayObjectInspector();
	}

    void DisplaySceneInspector() 
    {
        if (ImGui::CollapsingHeader("Scene", m_HeaderFlags))
        {
            ImGui::SameLine();
            if (ImGui::Button("Add Object")) ImGui::OpenPopup("Create_Object_Popup");
            ImGui::SameLine();
            if (ImGui::Button("Delete Object"))
            {
                m_ActiveScene->DestroyObject(m_SelectedObject);
                m_SelectedObject = nullptr;
            }

            if (ImGui::BeginPopup("Create_Object_Popup"))
            {
                ImGui::SeparatorText("Create Object");
                ImGui::InputText("Object Name", m_NewObjectNameBuffer, 64);
                if (ImGui::Button("Create")) 
                {
                    std::string objectName(m_NewObjectNameBuffer);
                    m_ActiveScene->CreateObject(objectName);
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }

            ImGuiSelectionBasicStorage selection;
            if (ImGui::BeginChild("##Basket", ImVec2(-FLT_MIN, ImGui::GetFontSize() * 20), ImGuiChildFlags_FrameStyle | ImGuiChildFlags_ResizeY)) 
            {
                ImGuiMultiSelectFlags flags = ImGuiMultiSelectFlags_BoxSelect1d | ImGuiMultiSelectFlags_SingleSelect | ImGuiMultiSelectFlags_SelectOnClickRelease;
                ImGuiMultiSelectIO* ms_io = ImGui::BeginMultiSelect(flags, selection.Size, 1);

                for (Object* obj : m_ActiveScene->GetHierarchy())
                {
                    bool item_is_selected = selection.Contains((ImGuiID)obj->GetUID());
                    ImGui::SetNextItemSelectionUserData(obj->GetUID());
                    ImGui::Selectable(obj->GetName().c_str(), item_is_selected, ImGuiSelectableFlags_None);

                    if (ImGui::BeginDragDropSource())
                    {
                        // Set payload to carry the index of our item (could be anything)
                        uint32_t objectUID = obj->GetUID();
                        ImGui::SetDragDropPayload("SCENE_OBJECT", &objectUID, sizeof(uint32_t));
                    
                        // Display preview (could be anything, e.g. when dragging an image we could decide to display
                        // the filename and a small preview of the image, etc.)
                        ImGui::Text(obj->GetName().c_str());
                        ImGui::EndDragDropSource();
                    }
                }

                ms_io = ImGui::EndMultiSelect();
                selection.ApplyRequests(ms_io);

                if (selection.Size > 0) 
                {
                    uint32_t UID;
                    void* it = NULL;
                    selection.GetNextSelectedItem(&it, &UID);
                    m_SelectedObject = m_ActiveScene->FindObjectByID(UID);
                }
                ImGui::EndChild();
            }
        }
    }

    void DisplayObjectInspector() 
    {
        if (ImGui::CollapsingHeader("Object Inspector", m_HeaderFlags))
        {
            if (m_SelectedObject != nullptr)
            {
                ImGui::Separator();
                ImGui::Text(m_SelectedObject->GetName().c_str());
                
                ImGui::SameLine();
                if (ImGui::Button("+"))
                    ImGui::OpenPopup("Add_Component_Popup");
                
                ImGui::SameLine();
                if (ImGui::Button("-"))
                    ImGui::OpenPopup("Remove_Component_Popup");

                if (ImGui::BeginPopup("Add_Component_Popup"))
                {
                    ImGui::SeparatorText("Add Component");
                    auto vector = ComponentRegistry::Instance().GetRegistryNames();
                    for (const char* name : vector)
                    {
                        if (ImGui::Selectable(name)) ComponentRegistry::Instance().ExecuteFactory(name, *m_SelectedObject);
                    }
                    ImGui::EndPopup();
                }

                if (ImGui::BeginPopup("Remove_Component_Popup"))
                {
                    ImGui::SeparatorText("Remove Component");
                    auto vector = m_SelectedObject->GetComponentList();
                    for (Component* component : vector)
                    {
                        if (ImGui::Selectable(component->GetName())) m_SelectedObject->RemoveComponent(component);
                    }
                    ImGui::EndPopup();
                }
                ImGui::Separator();

                m_SelectedObject->DrawEditor();
            }
        }
    }

private:
	Scene* m_ActiveScene;
    Object* m_SelectedObject = nullptr;

    ImGuiTreeNodeFlags m_HeaderFlags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_AllowOverlap;

    char m_NewObjectNameBuffer[64] = {"New Object"};
};