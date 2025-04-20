#include "Mat4.h"
#include "Vec3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Forgex::Math
{
    Mat4::Mat4() : m_Data{} {}

    Mat4::Mat4(float _scalar): m_Data{}
    {
        glm::mat4 matrix(_scalar);
        std::memcpy(m_Data, glm::value_ptr(matrix), sizeof(float) * 16);
    }

    Mat4::Mat4(const float* other) : m_Data{}
    {
        glm::mat4 matrix = glm::make_mat4(other);
        std::memcpy(m_Data, glm::value_ptr(matrix), sizeof(float) * 16);
    }

    const float* Mat4::Ptr() const
    {
        return m_Data;
    }

    Mat4 Mat4::operator*(const Mat4& other) const
    {
        glm::mat4 result = glm::make_mat4(m_Data) * glm::make_mat4(other.m_Data);
        return {glm::value_ptr(result)};
    }

    Vec3 Mat4::operator[](const int& i) const
    {
        glm::vec3 result = glm::make_mat4(m_Data)[i];
        return {result.x, result.y, result.z};
    }
}
