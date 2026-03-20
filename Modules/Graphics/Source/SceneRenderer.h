#pragma once
#include "GraphicsExports.h"
#include "Components/Renderable.h"

namespace Forgex::Graphics
{
    namespace Resources { struct RenderView; struct Framebuffer; }
    class SceneRenderProxy;
    
    class GRAPHICS_API SceneRenderer
    {
    public:
        SceneRenderer() = default;
        ~SceneRenderer() = default;

        void Render(const Resources::RenderView* renderView, std::vector<Renderable>* renderInfos);
        void RenderMap(const Resources::RenderView* renderView, std::vector<Renderable>* renderInfos);
    };
}
