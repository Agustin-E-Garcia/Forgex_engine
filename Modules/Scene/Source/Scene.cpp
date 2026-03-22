#include "Scene.h"
#include "Components/EntityInfo.h"

namespace Forgex::Scene
{
    Scene::Scene(const char* name) : m_Name(name) {}
    Scene::~Scene() {}

    int Scene::CreateEntity(const char* EntityName)
    {
        entt::entity entity = m_Registry.create();
        m_Registry.emplace<EntityInfo>(entity, EntityName);
        return (int)entity;
    }

    void Scene::DestroyEntity(int entity)
    {
        m_Registry.destroy((entt::entity)entity);
    }

    void Scene::Update(Core::Registry<Core::Interfaces::ISystem>& systemRegistry, float deltaTime)
    {
        for(auto& [index, system] : systemRegistry)
        {
            PROFILE_FUNCTION(system->GetName());
            system->Update(m_Registry, deltaTime);
        }
    }

    void Scene::Render(Core::Registry<Core::Interfaces::ISystem>& systemRegistry)
    {
        for(auto& [index, system] : systemRegistry)
        {
            PROFILE_FUNCTION(system->GetName());
            system->Render(m_Registry);
        }
    }
}
