#pragma once
#include <ForgexCore.h>
#include <entt.hpp>

namespace Forgex::Scene
{
    class Scene
    {
    public:
        Scene(const char* name);
        ~Scene();

        int CreateEntity(const char* EntityName);
        void DestroyEntity(int entity);

        template<typename T>
        T& AddComponent(int entity)
        {
            return m_Registry.emplace<T>((entt::entity)entity);
        }

        void Setup(Core::Registry<Core::Interfaces::ISystem>& systemRegistry);
        void Update(Core::Registry<Core::Interfaces::ISystem>& systemRegistry, float deltaTime);
        void Render(Core::Registry<Core::Interfaces::ISystem>& systemRegistry);

        entt::registry& GetRegistry() { return m_Registry; }
        const char* GetName() const { return m_Name; }

    private:
        const char* m_Name;
        entt::registry m_Registry;
    };
}
