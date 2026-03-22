#pragma once
#include "../Components/Renderable.h"
#include "../Resources/RenderView.h"

namespace Forgex::Graphics::Renderers
{
    class SceneRenderer
    {
    public:
        SceneRenderer() = default;
        ~SceneRenderer() = default;

        void Render(const Resources::RenderView* renderView, std::vector<Components::Renderable>* renderInfos);
        void RenderMap(const Resources::RenderView* renderView, std::vector<Components::Renderable>* renderInfos);
    };
}
