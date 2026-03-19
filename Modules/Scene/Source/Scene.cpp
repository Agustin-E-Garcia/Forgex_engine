#include "Scene.h"
#include <entt.hpp>
#include <ForgexDebugTools.h>
#include <string>

#include "Components/EntityInfo.h"
#include "Components/Transform.h"

namespace Forgex::Scene
{
    Scene::Scene(const char* name) : m_Name(name) {}
    Scene::~Scene()
    {
        for (auto& [name, system] : m_UpdateSystemMap)
            delete system;
        for (auto& [name, system] : m_RenderSystemMap)
            delete system;

        m_UpdateSystemMap.clear();
        m_RenderSystemMap.clear();
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

    void Scene::Update(float deltaTime)
    {
        for(auto& [name, system] : m_UpdateSystemMap)
        {
            PROFILE_FUNCTION(std::string(name));
            system->Run(m_Registry, deltaTime);
        }
    }

    void Scene::Render()
    {
        for(auto& [name, system] : m_RenderSystemMap)
        {
            PROFILE_FUNCTION(std::string(name));
            system->Run(m_Registry, 0);
        }
    }
}
