#pragma once
#include "MathExports.h"

namespace Forgex::Math
{
    struct MATH_API UVec2
    {
        unsigned int x, y;

        UVec2();
        UVec2(unsigned int _x, unsigned int _y);
        UVec2(unsigned int _scalar);

        const unsigned int* Ptr() const;
        
        static UVec2 Zero();
        
        UVec2 operator+ (const UVec2& other) const;
        UVec2 operator- (const UVec2& other) const;
        UVec2 operator* (const UVec2& other) const;
        UVec2 operator* (const unsigned int& scalar) const;
        unsigned int operator[] (const int& index) const;
        bool operator!= (const UVec2& other) const;
        bool operator== (const UVec2& other) const;
    };
}