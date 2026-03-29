#pragma once
#include "../Resources/RenderFrameData.h"
#include "../Components/Renderable.h"

namespace Forgex::Graphics::Renderers
{
    class SkyboxRenderer
    {
    public:
        void Render(const Resources::RenderFrameData& renderView, const Components::Renderable& renderable);
    };
}
