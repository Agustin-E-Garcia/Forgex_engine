#pragma once
#include "SceneExports.h"
#include "SystemBase.h"
#include <string>
#include <entt.hpp>

namespace Forgex::Scene
{
    class SCENE_API Scene
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

        template<class T>
        void RunSystem()
        {
            static_assert(std::is_base_of<ISystem, T>::value, "T must inherit from Component");
            T* system = new T();
            system->Run(m_Registry, 0.0f);
            delete system;
        }

        template<class T>
        void AddSystem()
        {
            static_assert(std::is_base_of<ISystem, T>::value, "T must inherit from Component");

            std::unordered_map<std::string, ISystem*>& systemMap = T::GetSystemType() == SystemType::UpdateSystem ? m_UpdateSystemMap : m_RenderSystemMap;
            systemMap[T::GetName()] = new T();
        }

        template<class T>
        void RemoveSystem()
        {
            static_assert(std::is_base_of<ISystem, T>::value, "T must inherit from ISystem");

            std::unordered_map<std::string, ISystem*>& systemMap = T::GetSystemType() == SystemType::UpdateSystem ? m_UpdateSystemMap : m_RenderSystemMap;
            auto it = systemMap.find(T::GetName());
            if(it == systemMap.end()) return;
            delete it->second;
            systemMap.erase(it);
        }

        void Update(float deltaTime);
        void Render();

        entt::registry& GetRegistry() { return m_Registry; }
        const char* GetName() const { return m_Name; }

    private:
        const char* m_Name;
        entt::registry m_Registry;
        std::unordered_map<std::string, ISystem*> m_UpdateSystemMap;
        std::unordered_map<std::string, ISystem*> m_RenderSystemMap;
    };
}
