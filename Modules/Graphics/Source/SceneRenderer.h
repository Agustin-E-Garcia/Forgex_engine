#pragma once
#include "GraphicsExports.h"

namespace Forgex::Graphics
{
    namespace Resources { struct RenderView; }
    class SceneRenderProxy;
    
    class GRAPHICS_API SceneRenderer
    {
    public:
        SceneRenderer() = default;
        ~SceneRenderer() = default;

        void RenderVoxelTerrain(const Resources::RenderView* renderView, const SceneRenderProxy* renderProxy);
        void Render(const Resources::RenderView* renderView, const SceneRenderProxy* renderProxy);
    };
}
