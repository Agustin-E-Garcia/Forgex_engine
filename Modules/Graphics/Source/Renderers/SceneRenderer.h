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

        void Render(const Resources::RenderFrameData& renderView, const std::vector<Components::Renderable>& renderInfos);
    };
}
