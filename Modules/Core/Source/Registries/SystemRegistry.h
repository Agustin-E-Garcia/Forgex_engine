#pragma once
#include <vector>
#include "../Interfaces/ISystem.h"

namespace Forgex::Core::Registries
{
    class SystemRegistry
    {
    public:
        void registerSystem(Interfaces::ISystem* system) { m_Systems.push_back(system); }

        void updateAll(entt::registry& registry, float deltaTime) 
        {
            for (auto* s : m_Systems)
                s->Update(registry, deltaTime);
        }

        const std::vector<Interfaces::ISystem*>& getSystems() const { return m_Systems; }

        std::vector<Interfaces::ISystem*>::iterator begin() { return m_Systems.begin(); }
        std::vector<Interfaces::ISystem*>::iterator end() { return m_Systems.end(); }

    private:
        std::vector<Interfaces::ISystem*> m_Systems;
    };
}
