#pragma once
#include <ForgexScene.h>
#include <ForgexDebugTools.h>

namespace Forgex::Core
{
    class MovementSystem : public Scene::PerEntitySystem<Scene::Transform, Scene::Speed>
    {
    public:
        SYSTEM_NAME(MovementSystem);

        void OnUpdate(const entt::entity entity, Scene::Transform& transform, Scene::Speed& speed) override
        {
        }
    };
}
