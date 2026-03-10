#pragma once
#include <ForgexScene.h>
#include <ForgexGraphics.h>

namespace Forgex::Core
{
    class RenderSystem : public Scene::ISystem
    {
        SYSTEM_NAME(RenderSystem);

        void Run(entt::registry& registry) override
        {
            auto cameraView = registry.view<Scene::Camera>(); //Use this to find the ActiveCamera
            auto renderView = registry.view<Scene::Render>(); //Use this to generate the render buffer and pass it to opengl for rendering
        }
    };
}
