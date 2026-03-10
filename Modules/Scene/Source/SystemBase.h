#pragma once
#include <entt.hpp>

#define SYSTEM_NAME(x) static const char* Name() { return #x; }

namespace Forgex::Scene
{
    class ISystem
    {
    public:
        virtual ~ISystem() = default;
        virtual void Run(entt::registry& registry) = 0;
    };

    template<typename... Components>
    class PerEntitySystem : public ISystem
    {
    public:
        virtual ~PerEntitySystem() = default;
        virtual void OnUpdate(const entt::entity entity, Components&... components) = 0;

        void Run(entt::registry& registry) override
        {
            auto view = registry.view<Components...>();
            view.each([this](const entt::entity entity, Components&... components) { OnUpdate(entity, components...); });
        }
    };
}
