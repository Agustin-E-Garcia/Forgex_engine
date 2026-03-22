#pragma once
#include <typeindex>
#include <unordered_map>

namespace Forgex::Core
{
    class EngineCore;

    class ServiceLocator
    {
    public:
        static ServiceLocator& Get();

        template<typename T>
        bool Register(T* service)
        {
            std::type_index index = std::type_index(typeid(T));

            if(m_Services.contains(index)) return false;
            m_Services[index] = service;

            return true;
        }

        template<typename T>
        T* Fetch()
        {
            std::type_index index = std::type_index(typeid(T));
            if(m_Services.contains(index)) return static_cast<T*>(m_Services[index]);

            return nullptr;
        }

    private:
        ServiceLocator() = default;
        std::unordered_map<std::type_index, void*> m_Services;
    };
}
