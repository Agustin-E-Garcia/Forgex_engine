#include "Scene.h"
#include <entt.hpp>
#include <ForgexDebugTools.h>

#include "Components/EntityInfo.h"
#include "Components/Transform.h"

namespace Forgex::Scene
{
    struct SceneData
    {
        entt::registry m_Registry;
    };

    Scene::Scene(const char* name) : m_Name(name) { m_Data = new SceneData(); }
    Scene::~Scene()
    {
        for (auto& [name, system] : m_SystemMap)
            delete system;

        m_SystemMap.clear();
    }

    int Scene::CreateEntity(const char* EntityName)
    {
        entt::entity entity = m_Data->m_Registry.create();
        m_Data->m_Registry.emplace<EntityInfo>(entity, EntityName);
        m_Data->m_Registry.emplace<Transform>(entity);
        return (int)entity;
    }

    void Scene::DestroyEntity(int entity)
    {
        m_Data->m_Registry.destroy((entt::entity)entity);
    }

    void Scene::Update(float deltatime)
    {
        for(auto& [name, system] : m_SystemMap)
        {
            system->Run(m_Data->m_Registry);
        }
    }
}
