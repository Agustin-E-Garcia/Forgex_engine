#pragma once
#include "SceneExports.h"
#include "SystemBase.h"
#include <map>
#include <string>

namespace Forgex::Scene
{
    struct SceneData;

    class SCENE_API Scene
    {
    public:
        Scene(const char* name);
        ~Scene();

        int CreateEntity(const char* EntityName);
        void DestroyEntity(int entity);

        template<class T>
        void AddSystem()
        {
            static_assert(std::is_base_of<ISystem, T>::value, "T must inherit from Component");
            m_SystemMap[T::Name()] = new T();
        }

        template<class T>
        void RemoveSystem()
        {
            static_assert(std::is_base_of<ISystem, T>::value, "T must inherit from ISystem");

            auto it = m_SystemMap.find(T::Name());
            if(it == m_SystemMap.end()) return;
            delete it->second;
            m_SystemMap.erase(it);
        }

        void Update(float deltaTime);

        const char* GetName() const { return m_Name; }

    private:
        const char* m_Name;
        SceneData* m_Data;
        std::map<std::string, ISystem*> m_SystemMap;
    };
}
