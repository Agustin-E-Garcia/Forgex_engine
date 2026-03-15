#include "VoxelMap.h"
#include "Resources/MarchingCubesTable.h"
#include <ForgexDebugTools.h>

namespace Forgex::Voxel
{
    VoxelMap::VoxelMap()
    {
        CalculateMesh();
        GenerateMesh();
    }

    VoxelMap::~VoxelMap() {}

    void VoxelMap::CalculateMesh()
    {
        glm::vec3 samples = (m_MapArea / glm::vec3(m_SampleDensity)) + glm::vec3(1.0f);
        int totalSamples = (int)samples.x * (int)samples.y * (int)samples.z;
        m_DensityValues.resize(totalSamples, 0);

        for(int i = 0; i < m_DensityValues.size(); i++)
        {
            glm::vec3 position = GetSampleWorldPosition(i);

            auto nearlyEqual = [](float a, float b) { return glm::abs(a - b) < 0.001f; };

            bool isBorder = nearlyEqual(position.x, 0) || nearlyEqual(position.x, m_MapArea.x) ||
                nearlyEqual(position.y, 0) || nearlyEqual(position.y, m_MapArea.y) ||
                nearlyEqual(position.z, 0) || nearlyEqual(position.z, m_MapArea.z);

            m_DensityValues[i] = isBorder ? 255 : 0;
        }
    }

    void VoxelMap::GenerateMesh()
    {
        int maxZ = 0;
        glm::vec3 samples = (m_MapArea / glm::vec3(m_SampleDensity)) + glm::vec3(1.0f);
        for (int z = 0; z < (int)samples.z - 1; z++)
        for (int y = 0; y < (int)samples.y - 1; y++)
        for (int x = 0; x < (int)samples.x - 1; x++)
        {
            if(z > maxZ) maxZ = z;

            // grab the 8 corners of THIS sample's cube
            uint8_t corner[8] = {
                m_DensityValues[GetSampleID(glm::vec3(x  , y  , z  ))],
                m_DensityValues[GetSampleID(glm::vec3(x+1, y  , z  ))],
                m_DensityValues[GetSampleID(glm::vec3(x+1, y+1, z  ))],
                m_DensityValues[GetSampleID(glm::vec3(x  , y+1, z  ))],
                m_DensityValues[GetSampleID(glm::vec3(x  , y  , z+1))],
                m_DensityValues[GetSampleID(glm::vec3(x+1, y  , z+1))],
                m_DensityValues[GetSampleID(glm::vec3(x+1, y+1, z+1))],
                m_DensityValues[GetSampleID(glm::vec3(x  , y+1, z+1))],
            };

            glm::vec3 positions[8] = {
                glm::vec3(x  , y  , z  ) * m_SampleDensity,
                glm::vec3(x+1, y  , z  ) * m_SampleDensity,
                glm::vec3(x+1, y+1, z  ) * m_SampleDensity,
                glm::vec3(x  , y+1, z  ) * m_SampleDensity,
                glm::vec3(x  , y  , z+1) * m_SampleDensity,
                glm::vec3(x+1, y  , z+1) * m_SampleDensity,
                glm::vec3(x+1, y+1, z+1) * m_SampleDensity,
                glm::vec3(x  , y+1, z+1) * m_SampleDensity,
            };


            // calculate cube index for THIS cube
            int cubeIndex = 0;
            for (int i = 0; i < 8; i++)
                if (corner[i] < m_Cutoff) cubeIndex |= (1 << i);

            // look up tables and generate triangles...
            if(Resources::edgeTable[cubeIndex] == 0) continue; // We skip fully air or full solid

            glm::vec3 edgeVerts[12];

            if (Resources::edgeTable[cubeIndex] & 1)    edgeVerts[0]  = Interpolate(positions[0], positions[1], corner[0], corner[1]);
            if (Resources::edgeTable[cubeIndex] & 2)    edgeVerts[1]  = Interpolate(positions[1], positions[2], corner[1], corner[2]);
            if (Resources::edgeTable[cubeIndex] & 4)    edgeVerts[2]  = Interpolate(positions[2], positions[3], corner[2], corner[3]);
            if (Resources::edgeTable[cubeIndex] & 8)    edgeVerts[3]  = Interpolate(positions[3], positions[0], corner[3], corner[0]);
            if (Resources::edgeTable[cubeIndex] & 16)   edgeVerts[4]  = Interpolate(positions[4], positions[5], corner[4], corner[5]);
            if (Resources::edgeTable[cubeIndex] & 32)   edgeVerts[5]  = Interpolate(positions[5], positions[6], corner[5], corner[6]);
            if (Resources::edgeTable[cubeIndex] & 64)   edgeVerts[6]  = Interpolate(positions[6], positions[7], corner[6], corner[7]);
            if (Resources::edgeTable[cubeIndex] & 128)  edgeVerts[7]  = Interpolate(positions[7], positions[4], corner[7], corner[4]);
            if (Resources::edgeTable[cubeIndex] & 256)  edgeVerts[8]  = Interpolate(positions[0], positions[4], corner[0], corner[4]);
            if (Resources::edgeTable[cubeIndex] & 512)  edgeVerts[9]  = Interpolate(positions[1], positions[5], corner[1], corner[5]);
            if (Resources::edgeTable[cubeIndex] & 1024) edgeVerts[10] = Interpolate(positions[2], positions[6], corner[2], corner[6]);
            if (Resources::edgeTable[cubeIndex] & 2048) edgeVerts[11] = Interpolate(positions[3], positions[7], corner[3], corner[7]);

            for (int i = 0; Resources::triTable[cubeIndex][i] != -1; i += 3)
            {
                PushVertex(edgeVerts[Resources::triTable[cubeIndex][i  ]]);
                PushVertex(edgeVerts[Resources::triTable[cubeIndex][i+2]]);
                PushVertex(edgeVerts[Resources::triTable[cubeIndex][i+1]]);
            }
        }

        LOG_CORE(Debug::Info, "Max Z reached: {0}", maxZ);
        LOG_CORE(Debug::Info, "Samples Z: {0}", samples.z);
    }

    glm::vec3 VoxelMap::Interpolate(glm::vec3 posA, glm::vec3 posB, uint8_t valA, uint8_t valB)
    {
        float t = (m_Cutoff - valA) / (float)(valB - valA);
        return posA + t * (posB - posA);
    }

    glm::vec3 VoxelMap::GetSampleWorldPosition(int sampleID)
    {
        glm::ivec3 samples = glm::ivec3((m_MapArea / glm::vec3(m_SampleDensity)) + glm::vec3(1.0f));

        int x = sampleID % samples.x;
        int y = (sampleID / samples.x) % samples.y;
        int z = sampleID / (samples.x * samples.y);

        return glm::vec3(x, y, z) * m_SampleDensity;
    }

    int VoxelMap::GetSampleID(glm::vec3 worldPosition)
    {
        glm::ivec3 samples = glm::ivec3((m_MapArea / glm::vec3(m_SampleDensity)) + glm::vec3(1.0f));

        int x = (int)(worldPosition.x / m_SampleDensity);
        int y = (int)(worldPosition.y / m_SampleDensity);
        int z = (int)(worldPosition.z / m_SampleDensity);

        return x + (y * samples.x) + (z * samples.x * samples.y);
    }

    void VoxelMap::PushVertex(glm::vec3 vertex)
    {
        m_Vertices.push_back(vertex.x);
        m_Vertices.push_back(vertex.y);
        m_Vertices.push_back(vertex.z);
    }
}
