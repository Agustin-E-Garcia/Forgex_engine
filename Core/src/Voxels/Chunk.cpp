#include "Chunk.h"
#include "../Log.h"
#include "ChunkManager.h"
#include "../Profiler.h"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/noise.hpp>
#include <algorithm>

static int s_GenerateVertexKey = -1;

Chunk::Chunk(glm::vec3 chunkPosition, int chunkSize) : m_ChunkPosition(chunkPosition), m_ChunkSize(chunkSize), m_UpToDate(false)
{
    m_Voxels.resize(m_ChunkSize * m_ChunkSizeY * m_ChunkSize);
}

Chunk::~Chunk() 
{
}

bool Chunk::Update(ChunkManager& manager)
{
    if (m_UpToDate) return false;

    GenerateVertices(manager);
    GenerateBuffers();
    UpdateDrawInfo();

    m_UpToDate = true;

    return true;
}

void Chunk::LoadChunk(glm::vec3 newPosition)
{
    SetPosition(newPosition);

    m_UpToDate = false;
}

int Chunk::FlattenIndex(int x, int y, int z)
{
    return (y * m_ChunkSize * m_ChunkSize) + (z * m_ChunkSize) + x;
}

void Chunk::GenerateVertices(ChunkManager& manager)
{
    Timer timer("Chunk::GenerateVertices", &s_GenerateVertexKey);

	m_Vertices.clear();

    Chunk* frontChunk = manager.GetChunkAtPosition(m_ChunkPosition + glm::vec3( 0, 0,  1));
    Chunk* backChunk  = manager.GetChunkAtPosition(m_ChunkPosition + glm::vec3( 0, 0, -1));
    Chunk* rightChunk = manager.GetChunkAtPosition(m_ChunkPosition + glm::vec3( 1, 0,  0));
    Chunk* leftChunk  = manager.GetChunkAtPosition(m_ChunkPosition + glm::vec3(-1, 0,  0));

	for (int y = 0; y < m_ChunkSizeY; y++)
	{
		for (int z = 0; z < m_ChunkSize; z++)
		{
            for (int x = 0; x < m_ChunkSize; x++)
            {
                int voxelIndex = FlattenIndex(x, y, z);
                if (!m_Voxels[voxelIndex].IsActive()) continue; // if voxel is not active, we don't render it

                bool shouldSkip = false;
                uint8_t voxelType = m_Voxels[voxelIndex].GetType();

                // Render Front triangles only if they are visible
                if (z + 1 == m_ChunkSize)
                {
                    shouldSkip = frontChunk != nullptr ? frontChunk->IsVoxelActive(x, y, 0) : true;
                }
                else shouldSkip = IsVoxelActive(x, y, z + 1);

                if (!shouldSkip)
                {
                    PushVertexData(0 + x, 0 + y, 1 + z, voxelType);
                    PushVertexData(1 + x, 0 + y, 1 + z, voxelType);
                    PushVertexData(1 + x, 1 + y, 1 + z, voxelType);

                    PushVertexData(1 + x, 1 + y, 1 + z, voxelType);
                    PushVertexData(0 + x, 1 + y, 1 + z, voxelType);
                    PushVertexData(0 + x, 0 + y, 1 + z, voxelType);
                }

                // Render Back triangles only if they are visible
                if (z - 1 < 0)
                {
                    shouldSkip = backChunk != nullptr ? backChunk->IsVoxelActive(x, y, m_ChunkSize - 1) : true;
                }
                else shouldSkip = IsVoxelActive(x, y, z - 1);

                if (!shouldSkip)
                {
                    PushVertexData(1 + x, 0 + y, 0 + z, voxelType);
                    PushVertexData(0 + x, 0 + y, 0 + z, voxelType);
                    PushVertexData(0 + x, 1 + y, 0 + z, voxelType);
                    
                    PushVertexData(0 + x, 1 + y, 0 + z, voxelType);
                    PushVertexData(1 + x, 1 + y, 0 + z, voxelType);
                    PushVertexData(1 + x, 0 + y, 0 + z, voxelType);
                }

                // Render Top triangles only if they are visible
                if (!IsVoxelActive(x, y + 1, z))
                {
                    PushVertexData(0 + x, 1 + y, 1 + z, voxelType);
                    PushVertexData(1 + x, 1 + y, 1 + z, voxelType);
                    PushVertexData(1 + x, 1 + y, 0 + z, voxelType);
                    
                    PushVertexData(1 + x, 1 + y, 0 + z, voxelType);
                    PushVertexData(0 + x, 1 + y, 0 + z, voxelType);
                    PushVertexData(0 + x, 1 + y, 1 + z, voxelType);
                }

                // Render Bottom triangles only if they are visible
                if (!IsVoxelActive(x, y - 1, z))
                {
                    PushVertexData(0 + x, 0 + y, 0 + z, voxelType);
                    PushVertexData(1 + x, 0 + y, 0 + z, voxelType);
                    PushVertexData(1 + x, 0 + y, 1 + z, voxelType);
                    
                    PushVertexData(1 + x, 0 + y, 1 + z, voxelType);
                    PushVertexData(0 + x, 0 + y, 1 + z, voxelType);
                    PushVertexData(0 + x, 0 + y, 0 + z, voxelType);
                }

                // Render Right triangles only if they are visible
                if (x + 1 == m_ChunkSize)
                {
                    shouldSkip = rightChunk != nullptr ? rightChunk->IsVoxelActive(0, y, z) : true;
                }
                else shouldSkip = IsVoxelActive(x + 1, y, z);

                if (!shouldSkip)
                {
                    PushVertexData(1 + x, 0 + y, 1 + z, voxelType);
                    PushVertexData(1 + x, 0 + y, 0 + z, voxelType);
                    PushVertexData(1 + x, 1 + y, 0 + z, voxelType);
                    
                    PushVertexData(1 + x, 1 + y, 0 + z, voxelType);
                    PushVertexData(1 + x, 1 + y, 1 + z, voxelType);
                    PushVertexData(1 + x, 0 + y, 1 + z, voxelType);
                }

                // Render Left triangles only if they are visible
                if (x - 1 < 0)
                {
                    shouldSkip = leftChunk != nullptr ? leftChunk->IsVoxelActive(m_ChunkSize - 1, y, z) : true;
                }
                else shouldSkip = IsVoxelActive(x - 1, y, z);

                if (!shouldSkip)
                {
                    PushVertexData(0 + x, 0 + y, 0 + z, voxelType);
                    PushVertexData(0 + x, 0 + y, 1 + z, voxelType);
                    PushVertexData(0 + x, 1 + y, 1 + z, voxelType);
                    
                    PushVertexData(0 + x, 1 + y, 1 + z, voxelType);
                    PushVertexData(0 + x, 1 + y, 0 + z, voxelType);
                    PushVertexData(0 + x, 0 + y, 0 + z, voxelType);
                }
			}
		}
	}
}

bool Chunk::TryGetVoxelAtPosition(float x, float y, float z, Voxel& voxel)
{
    int index = FlattenIndex(x, y, z);
    bool result = index < m_Voxels.size() && index >= 0;
    if (result) voxel = m_Voxels[index];
    return result;
}

bool Chunk::IsVoxelActive(float x, float y, float z) 
{
    Voxel voxel;
    bool result = TryGetVoxelAtPosition(x, y, z, voxel);
    return result ? voxel.IsActive() : false;
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

void Chunk::UpdateDrawInfo()
{
    m_DrawInfo.vertexBufferID = m_VertexBufferID;
    m_DrawInfo.modelMatrix = glm::translate(glm::mat4(1.0f), m_ChunkPosition * glm::vec3(m_ChunkSize));
    m_DrawInfo.indexCount = m_Vertices.size();
}