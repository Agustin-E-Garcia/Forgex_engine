#pragma once
#include "MathExports.h"

namespace Forgex::Math
{
    struct Vec3;
    
    struct MATH_API Mat4
    {
        float m_Data[16];

        Mat4();
        Mat4(float _scalar);
        Mat4(const float* other);

        const float* Ptr() const;
        
        Mat4 operator*(const Mat4& other) const;
        Vec3 operator[](const int& i) const;
    };
}