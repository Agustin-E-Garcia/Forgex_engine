#pragma once
#include "../Components/Renderable.h"
#include "../Resources/RenderFrameData.h"

namespace Forgex::Graphics::Renderers
{
    class SceneRenderer
    {
    public:
        SceneRenderer() = default;
        ~SceneRenderer() = default;

        void Render(const Resources::RenderFrameData& renderFrameData, const Components::Renderable& info);
    };
}
