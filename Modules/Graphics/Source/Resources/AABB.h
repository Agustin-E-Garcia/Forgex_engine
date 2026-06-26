#pragma once
#include <glm/glm.hpp>
#include <limits>
#include "CameraFrustum.h"
#include "glm/geometric.hpp"

namespace Forgex::Graphics::Resources
{
    struct AABB
    {
        glm::vec3 m_Min{ std::numeric_limits<float>::max() };
        glm::vec3 m_Max{ std::numeric_limits<float>::lowest() };

        void Encapsulate(const glm::vec3& point)
        {
            m_Min = glm::min(m_Min, point);
            m_Max = glm::max(m_Max, point);
        }

        AABB Transform(const glm::mat4& modelMatrix) const
        {
            glm::vec3 center  = (m_Min + m_Max) * 0.5f;
            glm::vec3 extents = (m_Max - m_Min) * 0.5f;

            glm::vec3 worldCenter = glm::vec3(modelMatrix * glm::vec4(center, 1.0f));

            glm::mat3 absBasis(glm::abs(glm::vec3(modelMatrix[0])),
                               glm::abs(glm::vec3(modelMatrix[1])),
                               glm::abs(glm::vec3(modelMatrix[2])));

            glm::vec3 worldExtents = absBasis * extents;
            return { worldCenter - worldExtents, worldCenter + worldExtents };
        }

        bool IsInFrustum(const Frustum& frustum) const
        {
            // generate the 8 points
            glm::vec3 points[8] 
            {
                { m_Min.x, m_Min.y, m_Min.z },
                { m_Max.x, m_Min.y, m_Min.z },
                { m_Min.x, m_Max.y, m_Min.z },
                { m_Max.x, m_Max.y, m_Min.z },
                { m_Min.x, m_Min.y, m_Max.z },
                { m_Max.x, m_Min.y, m_Max.z },
                { m_Min.x, m_Max.y, m_Max.z },
                { m_Max.x, m_Max.y, m_Max.z }
            };

            for(const glm::vec3 point : points)
            {
                bool inside = true;
                for (const Plane& plane : frustum.planes)
                {
                    float result = glm::dot(plane.m_Normal, point) + plane.m_DistanceToOrigin;
                    if(result < 0)
                    {
                        inside = false;
                        break;
                    }
                }
                if(inside) return true;
            }
            return false;
        }
    };
}
