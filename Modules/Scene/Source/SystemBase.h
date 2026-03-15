#pragma once
#include <entt.hpp>

#define SYSTEM_NAME(x) static const char* Name() { return #x; }

namespace Forgex::Scene
{
    class ISystem
    {
    public:
        virtual ~ISystem() = default;
        virtual void Update(entt::registry& registry, float deltaTime) = 0;
    };

    template<typename... Components>
    class PerEntitySystem : public ISystem
    {
    public:
        virtual ~PerEntitySystem() = default;
        virtual void OnUpdate(float deltaTime, const entt::entity entity, Components&... components) = 0;

        void Update(entt::registry& registry, float deltaTime) override
        {
            auto view = registry.view<Components...>();
            view.each([this, deltaTime](const entt::entity entity, Components&... components) { OnUpdate(deltaTime, entity, components...); });
        }
    };
}
