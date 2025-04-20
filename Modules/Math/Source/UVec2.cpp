#include "UVec2.h"
#include <glm/glm.hpp>

namespace Forgex::Math
{
    UVec2::UVec2() : x(0), y(0) {}
    UVec2::UVec2(unsigned int _x, unsigned int _y) : x(_x), y(_y) {}
    UVec2::UVec2(unsigned int _scalar) : x(_scalar), y(_scalar) {}

    const unsigned* UVec2::Ptr() const
    {
        return &x;
    }

    UVec2 UVec2::Zero() { return {}; }
    
    UVec2 UVec2::operator+(const UVec2& other) const
    {
        glm::uvec2 a(x, y);
        glm::uvec2 b(other.x, other.y);
        glm::uvec2 result = a + b;
        
        return {result.x, result.y};
    }

    UVec2 UVec2::operator-(const UVec2& other) const
    {
        glm::uvec2 a(x, y);
        glm::uvec2 b(other.x, other.y);
        glm::uvec2 result = a - b;

        return {result.x, result.y};
    }

    UVec2 UVec2::operator*(const UVec2& other) const
    {
        glm::uvec2 a(x, y);
        glm::uvec2 b(other.x, other.y);
        glm::uvec2 result = a * b;
        
        return {result.x, result.y};
    }

    UVec2 UVec2::operator* (const unsigned int& scalar) const
    {
        glm::uvec2 a(x, y);
        glm::uvec2 result = a * scalar;

        return {result.x, result.y};
    }

    unsigned int UVec2::operator[](const int& index) const
    {
        return x;
    }

    bool UVec2::operator!=(const UVec2& other) const
    {
        glm::uvec2 a(x, y);
        glm::uvec2 b(other.x, other.y);

        return a != b;
    }

    bool UVec2::operator==(const UVec2& other) const
    {
        glm::uvec2 a(x, y);
        glm::uvec2 b(other.x, other.y);

        return a == b;
    }
}
