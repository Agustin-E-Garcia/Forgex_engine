#pragma once
#include "../UI/GUIWindow.h"
#include <cstring>
#include <ForgexCore.h>

namespace Forgex::UI::Panels
{
	class SceneViewer : public GUIWindow
	{
	public:
		SceneViewer(Core::UISceneProxy* sceneProxy) : GUIWindow("SceneViewer", true), m_SceneProxy(sceneProxy) {}	
		~SceneViewer() {}

        Core::ObjectEntry GetSelectedObject() const { return m_SceneProxy->GetObjectByID(m_SelectedObject); }
        bool HasObjectSelected() const { return m_SelectedObject != 0; }
	protected:
		void OnDraw() override 
		{
			if (ImGui::CollapsingHeader("Scene", ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_AllowOverlap))
			{
				ImGui::SameLine();
				if (ImGui::Button("Add Object")) ImGui::OpenPopup("Create_Object_Popup");
				ImGui::SameLine();
				if (ImGui::Button("Delete Object")) 
				{
					if (m_SelectedObject) { m_SceneProxy->QueueDeleteOrder(m_SelectedObject); }
				}

				if (ImGui::BeginPopup("Create_Object_Popup"))
				{
					ImGui::SeparatorText("Create Object"); 
					ImGui::InputText("Object Name", m_NewObjectNameBuffer, 64);
					if (ImGui::Button("Create")) 
					{
						m_SceneProxy->QueueCreateOrder(m_NewObjectNameBuffer);
						ImGui::CloseCurrentPopup();

						std::strcpy(m_NewObjectNameBuffer, "New Object");
					}
					ImGui::EndPopup();
				}
			
				ImGuiSelectionBasicStorage selection;
				if (ImGui::BeginChild("##Basket", ImVec2(-FLT_MIN, ImGui::GetFontSize() * 20), ImGuiChildFlags_FrameStyle | ImGuiChildFlags_ResizeY)) 
				{
					ImGuiMultiSelectFlags flags = ImGuiMultiSelectFlags_BoxSelect1d | ImGuiMultiSelectFlags_SingleSelect | ImGuiMultiSelectFlags_SelectOnClickRelease;
					ImGuiMultiSelectIO* ms_io = ImGui::BeginMultiSelect(flags, selection.Size, 1);

					for (const Core::ObjectEntry obj : *m_SceneProxy)
					{
						bool item_is_selected = selection.Contains((ImGuiID)obj.m_ObjectID);
						ImGui::SetNextItemSelectionUserData(obj.m_ObjectID);
						ImGui::Selectable(obj.m_ObjectName.c_str(), item_is_selected, ImGuiSelectableFlags_None);

						if (ImGui::BeginDragDropSource())
						{
							// Set payload to carry the index of our item (could be anything)
							uint32_t objectUID = obj.m_ObjectID;
							ImGui::SetDragDropPayload("SCENE_OBJECT", &objectUID, sizeof(uint32_t));
							// Display preview (could be anything, e.g. when dragging an image we could decide to display
							// the filename and a small preview of the image, etc.)
							ImGui::Text(obj.m_ObjectName.c_str());
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
						m_SelectedObject = UID; 
					}
					ImGui::EndChild();
				}
			}
		}
		void Update() override {}
	private:
		Core::UISceneProxy* m_SceneProxy;

		uint32_t m_SelectedObject;
		char m_NewObjectNameBuffer[64] = { "New Object" };
	};
}
