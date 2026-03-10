#pragma once

namespace Forgex::Scene
{
    struct EntityInfo
    {
        const char* m_EntityName;

        EntityInfo(const char* name) : m_EntityName(name) {}
    };
}
