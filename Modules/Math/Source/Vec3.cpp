#include "Vec3.h"
#include <glm/glm.hpp>

namespace Forgex::Math
{
    Vec3::Vec3() : x(0), y(0), z(0) {}
    Vec3::Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vec3::Vec3(float _scalar) : x(_scalar), y(_scalar), z(_scalar) {}

    Vec3 Vec3::Zero() { return {}; }

    const float* Vec3::Ptr() { return &x; }

    Vec3 Vec3::operator+(const Vec3& other) const
    {
        glm::vec3 a(x, y ,z);
        glm::vec3 b(other.x, other.y, other.z);
        glm::vec3 result = a + b;

        return {result.x, result.y, result.z};
    }

    Vec3 Vec3::operator-(const Vec3& other) const
    {
        glm::vec3 a(x, y, z);
        glm::vec3 b(other.x, other.y, other.z);
        glm::vec3 result = a - b;

        return {result.x, result.y, result.z};
    }

    Vec3 Vec3::operator*(const Vec3& other) const
    {
        glm::vec3 a(x, y ,z);
        glm::vec3 b(other.x, other.y, other.z);
        glm::vec3 result = a * b;

        return {result.x, result.y, result.z};
    }

    Vec3 Vec3::operator* (const float& scalar) const
    {
        glm::vec3 a(x, y ,z);
        glm::vec3 result = a * scalar;

        return {result.x, result.y, result.z};
    }

    float Vec3::operator[](const int& index) const
    {
        return x;
    }

    bool Vec3::operator!=(const Vec3& other) const
    {
        glm::vec3 a(x, y ,z);
        glm::vec3 b(other.x, other.y, other.z);

        return a != b;
    }

    bool Vec3::operator==(const Vec3& other) const
    {
        glm::vec3 a(x, y ,z);
        glm::vec3 b(other.x, other.y, other.z);

        return a == b;
    }
}
