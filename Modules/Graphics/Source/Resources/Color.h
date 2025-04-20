#pragma once
#include "../Exports.h"

namespace Forgex::Graphics::Resources
{
    struct GRAPHICS_API Color
    {
        Color(float _red, float _blue, float _green, float _alpha)
            : red(_red), blue(_blue), green(_green), alpha(_alpha)
        {}
    
        float red, blue, green, alpha;
    };
}