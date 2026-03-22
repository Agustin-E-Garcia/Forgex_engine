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

    void Scene::Update(float deltaTime)
    {
    }

    void Scene::Render()
    {
    }
}
