#pragma once
#include <entt.hpp>

namespace Forgex::Core::Interfaces
{
    class ISystem
    {
    public:
        virtual ~ISystem() = default;

        virtual void Setup(entt::registry& registry) {}
        virtual void Update(entt::registry& registry, float deltaTime) {}
        virtual void Render(entt::registry& registry) {}
        virtual const char* GetName() = 0;
    };

    template<typename... Components>
    class PerEntitySystem : public ISystem
    {
    public:
        void Setup(entt::registry& registry) override 
        {
            auto view = registry.view<Components...>();
            view.each([this](const entt::entity& entity, Components&... components) { OnSetup(entity, components...); });
        }
        void Update(entt::registry& registry, float deltaTime) override 
        {
            auto view = registry.view<Components...>();
            view.each([this, deltaTime](const entt::entity& entity, Components&... components) { OnUpdate(deltaTime, entity, components...); });
        }
        void Render(entt::registry& registry) override 
        {
            auto view = registry.view<Components...>();
            view.each([this](const entt::entity& entity, Components&... components) { OnRender(entity, components...); });
        }

        virtual void OnSetup(const entt::entity& entity, Components&... components) {}
        virtual void OnUpdate(float deltaTime, const entt::entity& entity, Components&... components) {}
        virtual void OnRender(const entt::entity& entity, Components&... components) {}
    };
}
