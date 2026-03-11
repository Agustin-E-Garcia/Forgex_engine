#include "Scene.h"
#include <entt.hpp>
#include <ForgexDebugTools.h>

#include "Components/EntityInfo.h"
#include "Components/Transform.h"

namespace Forgex::Scene
{
    Scene::Scene(const char* name) : m_Name(name) {}
    Scene::~Scene()
    {
        for (auto& [name, system] : m_SystemMap)
            delete system;

        m_SystemMap.clear();
    }

    int Scene::CreateEntity(const char* EntityName)
    {
        entt::entity entity = m_Registry.create();
        m_Registry.emplace<EntityInfo>(entity, EntityName);
        m_Registry.emplace<Transform>(entity);
        return (int)entity;
    }

    void Scene::DestroyEntity(int entity)
    {
        m_Registry.destroy((entt::entity)entity);
    }

    void Scene::Update(float deltatime)
    {
        for(auto& [name, system] : m_SystemMap)
        {
            system->Update(m_Registry);
        }
    }
}
