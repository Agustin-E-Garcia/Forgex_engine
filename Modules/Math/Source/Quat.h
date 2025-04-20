#pragma once
#include "MathExports.h"

namespace Forgex::Math
{
    struct MATH_API Quat
    {
        float x, y, z, w;
        
        Quat();
        Quat(float _scalar);
        Quat(float _x, float _y, float _z, float _w);

        Quat operator*(const Quat& other);
    };
}
