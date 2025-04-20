#pragma once
#include "MathExports.h"
#include <cstdio>

namespace Forgex::Math
{
    struct MATH_API Vec3
    {
        float x, y, z;

        Vec3();
        Vec3(float _x, float _y, float _z);
        Vec3(float _scalar);

        static Vec3 Zero();
        
        Vec3 operator+ (const Vec3& other) const;
        Vec3 operator- (const Vec3& other) const;
        Vec3 operator* (const Vec3& other) const;
        Vec3 operator* (const float& scalar) const;
        float operator[] (const int& index) const;
        bool operator!= (const Vec3& other) const;
        bool operator== (const Vec3& other) const;

        static std::size_t GenHash(const Vec3& vector);
    };
}