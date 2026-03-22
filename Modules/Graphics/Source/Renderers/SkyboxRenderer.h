#pragma once
#include "../Resources/RenderView.h"
#include "../Components/Renderable.h"

namespace Forgex::Graphics::Renderers
{
    class SkyboxRenderer
    {
    public:
        void Render(const Resources::RenderView& renderView, const Components::Renderable& renderable);
    };
}
