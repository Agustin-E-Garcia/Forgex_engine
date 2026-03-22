#pragma once
#include <typeindex>
#include <unordered_map>

namespace Forgex::Core
{
    template<class BaseClass>
    class Registry
    {
    public:
        Registry() {}

        ~Registry()
        {
            for(auto& [ index, obj ] : m_RegistryMap)
                delete obj;
        }

        template<class T>
        T* Register()
        {
            static_assert(std::is_base_of<BaseClass, T>::value, "T must inherit from BaseClass");

            std::type_index index = std::type_index(typeid(T));

            if(m_RegistryMap.contains(index)) return nullptr;
            m_RegistryMap[index] = new T();

            return static_cast<T*>(m_RegistryMap[index]);
        }

        template<class T>
        T* Get()
        {
            static_assert(std::is_base_of<BaseClass, T>::value, "T must inherit from BaseClass");

            std::type_index index = std::type_index(typeid(T));

            if(m_RegistryMap.contains(index)) return static_cast<T*>(m_RegistryMap[index]);

            return nullptr;
        }

        template<class T>
        void Remove()
        {
            static_assert(std::is_base_of<BaseClass, T>::value, "T must inherit from BaseClass");

            std::type_index index = std::type_index(typeid(T));

            if(m_RegistryMap.contains(index))
            {
                delete m_RegistryMap[index];
                m_RegistryMap.erase(index);
            }
        }

        std::unordered_map<std::type_index, BaseClass*>::iterator begin() { return m_RegistryMap.begin(); }
        std::unordered_map<std::type_index, BaseClass*>::iterator end() { return m_RegistryMap.end(); }

    private:
        Registry(Registry& other) = delete;
        Registry(Registry&& other) = delete;
        Registry& operator=(const Registry& other) = delete;
        Registry& operator=(Registry&& other) = delete;

        std::unordered_map<std::type_index, BaseClass*> m_RegistryMap;
    };
}
