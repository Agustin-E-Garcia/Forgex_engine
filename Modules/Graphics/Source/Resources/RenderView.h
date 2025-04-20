#pragma once
#include <ForgexMath.h>

namespace Forgex::Graphics::Resources
{
    struct RenderView
    {
        Math::Mat4 m_ProjectionMatrix = Math::Mat4(1.0f);
        Math::Mat4 m_ViewMatrix = Math::Mat4(1.0f);
    };
}