#pragma once
#include "glm/matrix.hpp"
#include <glm/glm.hpp>

namespace Forgex::Graphics::Resources
{
    struct Plane
    {
        glm::vec3 m_Normal = glm::vec3(0);
        float m_DistanceToOrigin = 0;

        void Generate(glm::vec4 vector)
        {
            m_Normal = glm::vec3(vector);
            m_DistanceToOrigin = vector[3];
        }
    };

    enum Side
    {
        Left = 0,
        Right = 1,
        Top = 2,
        Bottom = 3,
        Near = 4,
        Far = 5
    };

    struct Frustum
    {
        Plane planes[6];

        Frustum() = default;

        Frustum(glm::mat4 viewProjection)
        {
            viewProjection = glm::transpose(viewProjection);

            planes[Side::Left].Generate(viewProjection[3] + viewProjection[0]);
            planes[Side::Right].Generate(viewProjection[3] - viewProjection[0]);

            planes[Side::Top].Generate(viewProjection[3] + viewProjection[1]);
            planes[Side::Bottom].Generate(viewProjection[3] - viewProjection[1]);

            planes[Side::Near].Generate(viewProjection[3] + viewProjection[2]);
            planes[Side::Far].Generate(viewProjection[3] - viewProjection[2]);
        }
    };
}
