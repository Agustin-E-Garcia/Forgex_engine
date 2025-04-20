#include "MathFunctions.h"
#include "Mat4.h"
#include "Vec3.h"
#include "Quat.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Forgex::Math
{
    float Pi() { return glm::pi<float>(); }

    float Clamp(float x, float minValue, float maxValue)
    {
        return glm::clamp(x, minValue, maxValue);
    }
    
    float Radians(float degrees)
    {
        return glm::radians(degrees);
    }

    
    Vec3 Normalize(Vec3 vector)
    {
        glm::vec3 normalizedVec = glm::normalize(glm::vec3(vector.x, vector.y, vector.z));
        return {normalizedVec.x, normalizedVec.y, normalizedVec.z};
    }


    Mat4 Translate(Mat4 matrix, Vec3 vector)
    {
        glm::mat4 a(*matrix.m_Data);
        glm::vec3 b(vector.x, vector.y, vector.z);
        a = glm::translate(a, b);

        return {&a[0][0]};
    }

    Mat4 Scale(Mat4 matrix, Vec3 scalar)
    {
        glm::mat4 a(*matrix.m_Data);
        glm::vec3 b(scalar.x, scalar.y, scalar.z);
        a = glm::scale(a, b);

        return {&a[0][0]};
    }

    Mat4 Mat4_Cast(Quat quaternion)
    {
        glm::quat a(quaternion.w, quaternion.x, quaternion.y, quaternion.z);
        glm::mat4 result = glm::mat4_cast(a);

        return {&result[0][0]};
    }

    Mat4 Perspective(float fovy, float aspect, float near, float far)
    {
        glm::mat4 result = glm::perspective(fovy, aspect, near, far);
        return {&result[0][0]};
    }

    Mat4 LookAt(Vec3 eye, Vec3 center, Vec3 up)
    {
        glm::vec3 a(eye.x, eye.y, eye.z);
        glm::vec3 b(center.x, center.y, center.z);
        glm::vec3 c(up.x, up.y, up.z);
        glm::mat4 result = glm::lookAt(a, b, c);

        return {&result[0][0]};
    }

    Mat4 GetRotationOnly(Mat4 matrix)
    {
        glm::mat4 a = glm::make_mat4(matrix.m_Data);
        return {glm::value_ptr(glm::mat4(glm::mat3(a)))};
    }


    Quat AngleAxis(float angle, Vec3 axis)
    {
        glm::vec3 a(axis.x, axis.y, axis.z);
        glm::quat result = glm::angleAxis(angle, a);

        return {result.x, result.y, result.z, result.w};
    }
}