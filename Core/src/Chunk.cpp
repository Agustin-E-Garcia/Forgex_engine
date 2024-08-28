#include "Chunk.h"
#include "Renderer.h"
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/noise.hpp"
#include "Log.h"

const int Chunk::s_ChunkSize = 32;

Chunk::Chunk()
{
	m_Voxels.reserve(std::pow(s_ChunkSize, 3));
	
	for (int i = 0; i < m_Voxels.capacity(); i++)
	{
		m_Voxels.push_back(new Voxel(VoxelType::Dirt));
	}

    GenerateVertices();
}

Chunk::~Chunk() 
{
    for (int i = m_Voxels.size() - 1; i >= 0; i--)
    {
        delete m_Voxels[i];
    }
}

DrawInfo Chunk::GetDrawInfo()
{
	DrawInfo info{};
	info.vertexBufferID = m_VertexBufferID;
	info.modelMatrix = glm::mat4(1.0f);
    info.indexCount = m_Vertices.size();
	return info;
}

int Chunk::FlattenIndex(int x, int y, int z)
{
    return (y * s_ChunkSize * s_ChunkSize) + (z * s_ChunkSize) + x;
}

void Chunk::GenerateVertices() 
{
	m_Vertices.clear();

	for (int y = 0; y < s_ChunkSize; y++)
	{
		for (int z = 0; z < s_ChunkSize; z++)
		{
            for (int x = 0; x < s_ChunkSize; x++)
            {
                int voxelIndex = FlattenIndex(x, y, z);
                if (!m_Voxels[voxelIndex]->IsActive()) continue; // if voxel is not active, we don't render it

                // Render Front triangles only if they are visible
                if (z + 1 >= s_ChunkSize || !m_Voxels[FlattenIndex(x, y, z + 1)]->IsActive())
                {
                    PushVertexData(0 + x, 0 + y, 1 + z, m_Voxels[voxelIndex]->GetType());
                    PushVertexData(1 + x, 0 + y, 1 + z, m_Voxels[voxelIndex]->GetType());
                    PushVertexData(1 + x, 1 + y, 1 + z, m_Voxels[voxelIndex]->GetType());

                    PushVertexData(1 + x, 1 + y, 1 + z, m_Voxels[voxelIndex]->GetType());
                    PushVertexData(0 + x, 1 + y, 1 + z, m_Voxels[voxelIndex]->GetType());
                    PushVertexData(0 + x, 0 + y, 1 + z, m_Voxels[voxelIndex]->GetType());
                }

                // Render Back triangles only if they are visible
                if (z - 1 < 0 || !m_Voxels[FlattenIndex(x, y, z - 1)]->IsActive())
                {
                    PushVertexData(1 + x, 0 + y, 0 + z, m_Voxels[voxelIndex]->GetType());
                    PushVertexData(0 + x, 0 + y, 0 + z, m_Voxels[voxelIndex]->GetType());
                    PushVertexData(0 + x, 1 + y, 0 + z, m_Voxels[voxelIndex]->GetType());
                    
                    PushVertexData(0 + x, 1 + y, 0 + z, m_Voxels[voxelIndex]->GetType());
                    PushVertexData(1 + x, 1 + y, 0 + z, m_Voxels[voxelIndex]->GetType());
                    PushVertexData(1 + x, 0 + y, 0 + z, m_Voxels[voxelIndex]->GetType());
                }

                // Render Top triangles only if they are visible
                if (y + 1 >= s_ChunkSize || !m_Voxels[FlattenIndex(x, y + 1, z)]->IsActive())
                {
                    PushVertexData(0 + x, 1 + y, 1 + z, m_Voxels[voxelIndex]->GetType());
                    PushVertexData(1 + x, 1 + y, 1 + z, m_Voxels[voxelIndex]->GetType());
                    PushVertexData(1 + x, 1 + y, 0 + z, m_Voxels[voxelIndex]->GetType());
                    
                    PushVertexData(1 + x, 1 + y, 0 + z, m_Voxels[voxelIndex]->GetType());
                    PushVertexData(0 + x, 1 + y, 0 + z, m_Voxels[voxelIndex]->GetType());
                    PushVertexData(0 + x, 1 + y, 1 + z, m_Voxels[voxelIndex]->GetType());
                }

                // Render Bottom triangles only if they are visible
                if (y - 1 < 0 || !m_Voxels[FlattenIndex(x, y - 1, z)]->IsActive())
                {
                    PushVertexData(0 + x, 0 + y, 0 + z, m_Voxels[voxelIndex]->GetType());
                    PushVertexData(1 + x, 0 + y, 0 + z, m_Voxels[voxelIndex]->GetType());
                    PushVertexData(1 + x, 0 + y, 1 + z, m_Voxels[voxelIndex]->GetType());
                    
                    PushVertexData(1 + x, 0 + y, 1 + z, m_Voxels[voxelIndex]->GetType());
                    PushVertexData(0 + x, 0 + y, 1 + z, m_Voxels[voxelIndex]->GetType());
                    PushVertexData(0 + x, 0 + y, 0 + z, m_Voxels[voxelIndex]->GetType());
                }

                // Render Right triangles only if they are visible
                if (x + 1 >= s_ChunkSize || !m_Voxels[FlattenIndex(x + 1, y, z)]->IsActive())
                {
                    PushVertexData(1 + x, 0 + y, 1 + z, m_Voxels[voxelIndex]->GetType());
                    PushVertexData(1 + x, 0 + y, 0 + z, m_Voxels[voxelIndex]->GetType());
                    PushVertexData(1 + x, 1 + y, 0 + z, m_Voxels[voxelIndex]->GetType());
                    
                    PushVertexData(1 + x, 1 + y, 0 + z, m_Voxels[voxelIndex]->GetType());
                    PushVertexData(1 + x, 1 + y, 1 + z, m_Voxels[voxelIndex]->GetType());
                    PushVertexData(1 + x, 0 + y, 1 + z, m_Voxels[voxelIndex]->GetType());
                }

                // Render Left triangles only if they are visible
                if (x - 1 < 0 || !m_Voxels[FlattenIndex(x - 1, y, z)]->IsActive())
                {
                    PushVertexData(0 + x, 0 + y, 0 + z, m_Voxels[voxelIndex]->GetType());
                    PushVertexData(0 + x, 0 + y, 1 + z, m_Voxels[voxelIndex]->GetType());
                    PushVertexData(0 + x, 1 + y, 1 + z, m_Voxels[voxelIndex]->GetType());
                    
                    PushVertexData(0 + x, 1 + y, 1 + z, m_Voxels[voxelIndex]->GetType());
                    PushVertexData(0 + x, 1 + y, 0 + z, m_Voxels[voxelIndex]->GetType());
                    PushVertexData(0 + x, 0 + y, 0 + z, m_Voxels[voxelIndex]->GetType());
                }
			}
		}
	}

    GenerateBuffers();
}

void Chunk::PushVertexData(uint8_t x, uint8_t y, uint8_t z, uint8_t blockType)
{
    // First we pack the values into a 32-bit integer
    uint32_t packedValue = (static_cast<uint32_t>(x) << 24) | (static_cast<uint32_t>(y) << 16) | (static_cast<uint32_t>(z) << 8) | (static_cast<uint32_t>(blockType));
    m_Vertices.push_back(packedValue);
}

void Chunk::GenerateBuffers()
{
	Renderer::DeleteBuffer(m_VertexBufferID);
	m_VertexBufferID = Renderer::GenerateBuffer(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(uint32_t), m_Vertices.data());
}

Voxel* Chunk::GetVoxel(int x, int y, int z) 
{
	return nullptr;
}