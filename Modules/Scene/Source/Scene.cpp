#include "Scene.h"
#include "Components/EntityInfo.h"

namespace Forgex::Scene
{
    Scene::Scene(const char* name) : m_Name(name) {}
    Scene::~Scene() {}

    int Scene::CreateEntity(const char* EntityName)
    {
        entt::entity entity = m_Registry.create();
        m_Registry.emplace<Components::EntityInfo>(entity, EntityName);
        return (int)entity;
    }

    void Scene::DestroyEntity(int entity)
    {
        m_Registry.destroy((entt::entity)entity);
    }

    void Scene::Setup(DataStructures::Registry<Core::Interfaces::ISystem>& systemRegistry)
    {
        for(auto& [index, system] : systemRegistry)
            system->Setup(m_Registry);
    }

    void Scene::Update(DataStructures::Registry<Core::Interfaces::ISystem>& systemRegistry, float deltaTime)
    {
        PROFILE_FUNCTION("Update Systems");
        for(auto& [index, system] : systemRegistry)
        {
            if(!system->RunUpdate()) continue;

            PROFILE_FUNCTION(system->GetName());
            system->Update(m_Registry, deltaTime);
        }
    }

    void Scene::Render(DataStructures::Registry<Core::Interfaces::ISystem>& systemRegistry)
    {
        PROFILE_FUNCTION("Render Systems");
        for(auto& [index, system] : systemRegistry)
        {
            if(!system->RunRender()) continue;

            PROFILE_FUNCTION(system->GetName());
            system->Render(m_Registry);
        }
    }
}
