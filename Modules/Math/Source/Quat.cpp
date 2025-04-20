#include "Quat.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Forgex::Math
{
    Quat::Quat() : x(0), y(0), z(0), w(0) {}
    Quat::Quat(float _scalar) : x(_scalar), y(_scalar), z(_scalar), w(_scalar) {}
    Quat::Quat(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}

    Quat Quat::operator*(const Quat& other)
    {
        glm::quat a(w, x ,y, z);
        glm::quat b(other.w, other.x, other.y, other.z);
        glm::quat result = a * b;

        return {result.x, result.y, result.z, result.w};
    }
}
