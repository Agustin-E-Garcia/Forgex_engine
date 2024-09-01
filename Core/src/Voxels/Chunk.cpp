#include "Chunk.h"
#include "../Renderer.h"
#include "../Log.h"
#include "ChunkManager.h"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

Chunk::Chunk(glm::vec3 chunkPosition, int chunkSize) : m_ChunkPosition(chunkPosition), m_ChunkSize(chunkSize), m_UpToDate(false)
{
	m_Voxels.reserve(m_ChunkSize * m_ChunkSizeY * m_ChunkSize);
}

Chunk::~Chunk() 
{
    for (int i = m_Voxels.size() - 1; i >= 0; i--)
    {
        delete m_Voxels[i];
    }
}

void Chunk::Update(ChunkManager& manager)
{
    if (m_UpToDate) return;

    GenerateVertices(manager);
    m_UpToDate = true;
}

void Chunk::LoadChunk()
{
    for (int i = 0; i < m_Voxels.capacity(); i++)
    {
        m_Voxels.push_back(new Voxel(VoxelType::Dirt));
    }
}

DrawInfo Chunk::GetDrawInfo()
{
	DrawInfo info{};
	info.vertexBufferID = m_VertexBufferID;
    info.modelMatrix = glm::translate(glm::mat4(1.0f), m_ChunkPosition * glm::vec3(m_ChunkSize));
    info.indexCount = m_Vertices.size();
	return info;
}

int Chunk::FlattenIndex(int x, int y, int z)
{
    return (y * m_ChunkSize * m_ChunkSize) + (z * m_ChunkSize) + x;
}

void Chunk::GenerateVertices(ChunkManager& manager) 
{
	m_Vertices.clear();

	for (int y = 0; y < m_ChunkSizeY; y++)
	{
		for (int z = 0; z < m_ChunkSize; z++)
		{
            for (int x = 0; x < m_ChunkSize; x++)
            {
                int voxelIndex = FlattenIndex(x, y, z);
                if (!m_Voxels[voxelIndex]->IsActive()) continue; // if voxel is not active, we don't render it

                bool shouldSkip = false;
                Chunk* otherChunk;

                // Render Front triangles only if they are visible
                if (z + 1 == m_ChunkSize)
                {
                    otherChunk = manager.GetChunkAtPosition(m_ChunkPosition + glm::vec3(0, 0, 1));
                    shouldSkip = otherChunk != nullptr ? otherChunk->IsVoxelActive(glm::vec3(x, y, 0)) : false;
                }
                else shouldSkip = IsVoxelActive(glm::vec3(x, y, z + 1));

                if (!shouldSkip)
                {
                    PushVertexData(0 + x, 0 + y, 1 + z, m_Voxels[voxelIndex]->GetType());
                    PushVertexData(1 + x, 0 + y, 1 + z, m_Voxels[voxelIndex]->GetType());
                    PushVertexData(1 + x, 1 + y, 1 + z, m_Voxels[voxelIndex]->GetType());

                    PushVertexData(1 + x, 1 + y, 1 + z, m_Voxels[voxelIndex]->GetType());
                    PushVertexData(0 + x, 1 + y, 1 + z, m_Voxels[voxelIndex]->GetType());
                    PushVertexData(0 + x, 0 + y, 1 + z, m_Voxels[voxelIndex]->GetType());
                }

                // Render Back triangles only if they are visible
                if (z - 1 < 0)
                {
                    otherChunk = manager.GetChunkAtPosition(m_ChunkPosition + glm::vec3(0, 0, -1));
                    shouldSkip = otherChunk != nullptr ? otherChunk->IsVoxelActive(glm::vec3(x, y, m_ChunkSize - 1)) : false;
                }
                else shouldSkip = IsVoxelActive(glm::vec3(x, y, z - 1));

                if (!shouldSkip)
                {
                    PushVertexData(1 + x, 0 + y, 0 + z, m_Voxels[voxelIndex]->GetType());
                    PushVertexData(0 + x, 0 + y, 0 + z, m_Voxels[voxelIndex]->GetType());
                    PushVertexData(0 + x, 1 + y, 0 + z, m_Voxels[voxelIndex]->GetType());
                    
                    PushVertexData(0 + x, 1 + y, 0 + z, m_Voxels[voxelIndex]->GetType());
                    PushVertexData(1 + x, 1 + y, 0 + z, m_Voxels[voxelIndex]->GetType());
                    PushVertexData(1 + x, 0 + y, 0 + z, m_Voxels[voxelIndex]->GetType());
                }

                // Render Top triangles only if they are visible
                if (!IsVoxelActive(glm::vec3(x, y + 1, z)))
                {
                    PushVertexData(0 + x, 1 + y, 1 + z, m_Voxels[voxelIndex]->GetType());
                    PushVertexData(1 + x, 1 + y, 1 + z, m_Voxels[voxelIndex]->GetType());
                    PushVertexData(1 + x, 1 + y, 0 + z, m_Voxels[voxelIndex]->GetType());
                    
                    PushVertexData(1 + x, 1 + y, 0 + z, m_Voxels[voxelIndex]->GetType());
                    PushVertexData(0 + x, 1 + y, 0 + z, m_Voxels[voxelIndex]->GetType());
                    PushVertexData(0 + x, 1 + y, 1 + z, m_Voxels[voxelIndex]->GetType());
                }

                // Render Bottom triangles only if they are visible
                if (!IsVoxelActive(glm::vec3(x, y - 1, z)))
                {
                    PushVertexData(0 + x, 0 + y, 0 + z, m_Voxels[voxelIndex]->GetType());
                    PushVertexData(1 + x, 0 + y, 0 + z, m_Voxels[voxelIndex]->GetType());
                    PushVertexData(1 + x, 0 + y, 1 + z, m_Voxels[voxelIndex]->GetType());
                    
                    PushVertexData(1 + x, 0 + y, 1 + z, m_Voxels[voxelIndex]->GetType());
                    PushVertexData(0 + x, 0 + y, 1 + z, m_Voxels[voxelIndex]->GetType());
                    PushVertexData(0 + x, 0 + y, 0 + z, m_Voxels[voxelIndex]->GetType());
                }

                // Render Right triangles only if they are visible
                if (x + 1 == m_ChunkSize)
                {
                    otherChunk = manager.GetChunkAtPosition(m_ChunkPosition + glm::vec3(1, 0, 0));
                    shouldSkip = otherChunk != nullptr ? otherChunk->IsVoxelActive(glm::vec3(0, y, z)) : false;
                }
                else shouldSkip = IsVoxelActive(glm::vec3(x + 1, y, z));

                if (!shouldSkip)
                {
                    PushVertexData(1 + x, 0 + y, 1 + z, m_Voxels[voxelIndex]->GetType());
                    PushVertexData(1 + x, 0 + y, 0 + z, m_Voxels[voxelIndex]->GetType());
                    PushVertexData(1 + x, 1 + y, 0 + z, m_Voxels[voxelIndex]->GetType());
                    
                    PushVertexData(1 + x, 1 + y, 0 + z, m_Voxels[voxelIndex]->GetType());
                    PushVertexData(1 + x, 1 + y, 1 + z, m_Voxels[voxelIndex]->GetType());
                    PushVertexData(1 + x, 0 + y, 1 + z, m_Voxels[voxelIndex]->GetType());
                }

                // Render Left triangles only if they are visible
                if (x - 1 < 0)
                {
                    otherChunk = manager.GetChunkAtPosition(m_ChunkPosition + glm::vec3(-1, 0, 0));
                    shouldSkip = otherChunk != nullptr ? otherChunk->IsVoxelActive(glm::vec3(m_ChunkSize - 1, y, z)) : false;
                }
                else shouldSkip = IsVoxelActive(glm::vec3(x - 1, y, z));

                if (!shouldSkip)
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

Voxel* Chunk::GetVoxelAtPosition(glm::vec3 position)
{
    int index = FlattenIndex(position.x, position.y, position.z);
    return index < m_Voxels.size() && index >= 0 ? m_Voxels[index] : nullptr;
}

bool Chunk::IsVoxelActive(glm::vec3 position) 
{
    Voxel* voxel = GetVoxelAtPosition(position);
    return voxel != nullptr ? voxel->IsActive() : false;
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