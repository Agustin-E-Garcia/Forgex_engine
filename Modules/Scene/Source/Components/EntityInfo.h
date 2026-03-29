#pragma once

namespace Forgex::Scene::Components
{
    struct EntityInfo
    {
        const char* m_EntityName = "New Entity";

        EntityInfo(const char* name) : m_EntityName(name) {}
    };
}
