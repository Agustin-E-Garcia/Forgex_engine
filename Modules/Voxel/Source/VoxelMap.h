#pragma once
#include "VoxelExports.h"
#include <glm/glm.hpp>
#include <vector>

namespace Forgex::Voxel
{
    class VOXEL_API VoxelMap
    {
    public:
        VoxelMap();
        ~VoxelMap();

        void CalculateMesh();
        void GenerateMesh();

        glm::vec3 Interpolate(glm::vec3 posA, glm::vec3 posB, uint8_t valA, uint8_t valB);
        glm::vec3 GetSampleWorldPosition(int sampleID);
        int GetSampleID(glm::vec3 worldPosition);

        void PushVertex(glm::vec3 vertex);
        float* GetVertices() { return m_Vertices.data(); }
        int GetVertexCount() { return m_Vertices.size(); }

    private:
        glm::vec3 m_MapArea = glm::vec3(20.0f);
        float m_SampleDensity = 1.0f;
        int m_Cutoff = 175;

        std::vector<uint8_t> m_DensityValues;

        std::vector<float> m_Vertices;
        std::vector<int> m_Indices;
    };
}
