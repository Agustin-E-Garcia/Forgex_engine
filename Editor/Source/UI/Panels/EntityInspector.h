#pragma once
#include "../GUIWindow.h"
#include <imgui.h>
#include <ForgexCore.h>
#include <ForgexScene.h>
#include <ForgexGraphics.h>
#include <glm/gtc/type_ptr.hpp>

namespace Forgex::Editor::UI::Panels
{
    class EntityInspectorPanel : public GUIWindow
    {
    public:
        EntityInspectorPanel() : GUIWindow("Entity Inspector", false) {}
        ~EntityInspectorPanel() {}

    protected:
        void OnDraw() override
        {
            Scene::SceneManager* sceneManager = GET_SERVICE(Scene::SceneManager);
            Scene::Scene* scene = sceneManager ? sceneManager->GetActiveScene() : nullptr;

            float listWidth = 200.0f;
            ImGui::BeginChild("##entity_list", ImVec2(listWidth, 0.0f), true);

            ImGui::TextUnformatted("Entities");
            ImGui::Separator();

            if (scene)
            {
                auto& registry = scene->GetRegistry();
                auto view = registry.view<Scene::Components::EntityInfo>();

                for (auto entity : view)
                {
                    auto& info = view.get<Scene::Components::EntityInfo>(entity);
                    bool selected = (m_SelectedEntity == entity);
                    if (ImGui::Selectable(info.m_EntityName, selected))
                        m_SelectedEntity = entity;
                }
            }

            ImGui::EndChild();

            ImGui::SameLine();

            ImGui::BeginChild("##entity_properties", ImVec2(0.0f, 0.0f), true);

            if (scene && m_SelectedEntity != entt::null)
            {
                auto& registry = scene->GetRegistry();

                if (!registry.valid(m_SelectedEntity))
                {
                    m_SelectedEntity = entt::null;
                    ImGui::TextDisabled("Select an entity to inspect");
                    ImGui::EndChild();
                    return;
                }

                auto& info = registry.get<Scene::Components::EntityInfo>(m_SelectedEntity);
                ImGui::Text("Entity: %s", info.m_EntityName);
                ImGui::Separator();

                DrawTransform(registry);
                DrawCamera(registry);
                DrawPointLight(registry);
                DrawRenderable(registry);
            }
            else
            {
                ImGui::TextDisabled("Select an entity to inspect");
            }

            ImGui::EndChild();
        }

    private:
        entt::entity m_SelectedEntity = entt::null;

        void DrawTransform(entt::registry& registry)
        {
            if (!registry.all_of<Core::Components::Transform>(m_SelectedEntity))
                return;

            if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
            {
                auto& t = registry.get<Core::Components::Transform>(m_SelectedEntity);

                if (ImGui::DragFloat3("Position", glm::value_ptr(t.m_Position), 0.1f))
                    t.m_Dirty = true;

                if (ImGui::DragFloat3("Rotation", glm::value_ptr(t.m_Rotation), 0.5f))
                    t.m_Dirty = true;

                if (ImGui::DragFloat3("Scale",    glm::value_ptr(t.m_Scale),    0.01f))
                    t.m_Dirty = true;
            }
        }

        void DrawCamera(entt::registry& registry)
        {
            if (!registry.all_of<Graphics::Components::Camera>(m_SelectedEntity))
                return;

            if (ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_DefaultOpen))
            {
                auto& cam = registry.get<Graphics::Components::Camera>(m_SelectedEntity);

                ImGui::Checkbox("Active Camera", &cam.m_IsActiveCamera);
                ImGui::DragFloat("Field of View", &cam.m_FieldOfView, 0.5f, 1.0f, 179.0f);
                ImGui::DragFloat("Near Plane",    &cam.m_NearPlane,   0.001f, 0.001f, 10.0f);
                ImGui::DragFloat("Far Plane",     &cam.m_FarPlane,    1.0f, 1.0f, 10000.0f);
            }
        }

        void DrawPointLight(entt::registry& registry)
        {
            if (!registry.all_of<Graphics::Components::PointLight>(m_SelectedEntity))
                return;

            if (ImGui::CollapsingHeader("Point Light", ImGuiTreeNodeFlags_DefaultOpen))
            {
                auto& light = registry.get<Graphics::Components::PointLight>(m_SelectedEntity);

                ImGui::ColorEdit3("Color",     glm::value_ptr(light.color));
                ImGui::DragFloat("Radius",     &light.radius,    0.1f, 0.0f, 1000.0f);
                ImGui::DragFloat("Intensity",  &light.intensity, 0.01f, 0.0f, 10.0f);
            }
        }

        void DrawRenderable(entt::registry& registry)
        {
            if (!registry.all_of<Graphics::Components::Renderable>(m_SelectedEntity))
                return;

            if (ImGui::CollapsingHeader("Renderable", ImGuiTreeNodeFlags_DefaultOpen))
            {
                auto& renderable = registry.get<Graphics::Components::Renderable>(m_SelectedEntity);

                ImGui::Text("Mesh:");
                ImGui::SameLine();
                if (renderable.m_MeshAsset.IsValid())
                    ImGui::TextUnformatted(renderable.m_MeshAsset->GetPath().c_str());
                else
                    ImGui::TextDisabled("(none)");

                ImGui::Text("Material:");
                ImGui::SameLine();
                if (renderable.m_MaterialAsset.IsValid())
                    ImGui::TextUnformatted(renderable.m_MaterialAsset->GetPath().c_str());
                else
                    ImGui::TextDisabled("(none)");
            }
        }
    };
}
