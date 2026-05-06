#pragma once
#include "CoreExports.h"
#include <typeindex>
#include <unordered_map>
#include <utility>

namespace Forgex::Core
{
    class EngineCore;

    class CORE_API ServiceLocator
    {
    public:
        static ServiceLocator& Get();

        template<typename T, typename... Args>
        bool Register(Args&&... args)
        {
            std::type_index index = std::type_index(typeid(T));

            if(m_Services.contains(index)) return false;
            m_Services[index] = new T(std::forward<Args>(args)...);

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

#define GET_SERVICE(x) Forgex::Core::ServiceLocator::Get().Fetch<x>()
}
