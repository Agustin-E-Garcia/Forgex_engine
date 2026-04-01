#pragma once
#include <glm/glm.hpp>

namespace Forgex::Scene::Components
{
    struct EntityInfo
    {
        const char* m_EntityName = "New Entity";
        bool m_IsActive = true;

        bool m_DrawGizmo = false;
        glm::vec3 m_GizmoColor = glm::vec3(1.0f);

        EntityInfo(const char* name) : m_EntityName(name), m_IsActive(true), m_DrawGizmo(false), m_GizmoColor(glm::vec3(1.0f)) {}
    };
}
