#pragma once
#include <entt.hpp>

#define SYSTEM_NAME(x) static const char* GetName() { return #x; }
#define SYSTEM_TYPE(x) static const Scene::SystemType GetSystemType() { return Scene::SystemType::x; }

namespace Forgex::Scene
{
    enum SystemType
    {
        UpdateSystem,
        RenderSystem,
    };

    class ISystem
    {
    public:
        virtual ~ISystem() = default;
        virtual void Run(entt::registry& registry, float deltaTime) = 0;
    };

    template<typename... Components>
    class PerEntitySystem : public ISystem
    {
    public:
        virtual ~PerEntitySystem() = default;
        virtual void OnUpdate(float deltaTime, const entt::entity entity, Components&... components) = 0;

        void Run(entt::registry& registry, float deltaTime) override
        {
            auto view = registry.view<Components...>();
            view.each([this, deltaTime](const entt::entity entity, Components&... components) { OnUpdate(deltaTime, entity, components...); });
        }
    };
}
