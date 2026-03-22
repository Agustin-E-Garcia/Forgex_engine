#pragma once
#include <entt.hpp>

namespace Forgex::Core::Interfaces
{
    class ISystem
    {
    public:
        virtual ~ISystem() = default;

        virtual void Update(entt::registry& registry, float deltaTime) {}
        virtual void Render(entt::registry& registry) {}
        virtual const char* GetName() = 0;
    };
}
